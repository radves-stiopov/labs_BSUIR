from django.shortcuts import render, redirect, get_object_or_404
from django.urls import reverse
from django.template.loader import render_to_string
from django.http import HttpResponseBadRequest, HttpResponse

import os
import re
import numpy as np
from sklearn.feature_extraction.text import TfidfVectorizer

from .models import Document, Summary, Sentence, Keyword
from .utils.file_reader import extract_text_from_file
from .utils.summarizer import RUSSIAN_STOPWORDS
# Импортируем вашу функцию для работы с локальной Ollama
from .utils.ollama_client import generate_keywords_via_ollama


def index(request):
    """Главная страница с формой загрузки документов."""
    return render(request, "referate_creator_app/index.html")


def documents_list(request):
    """Страница со списком загруженных документов."""
    documents = Document.objects.all().order_by("-upload_date")
    return render(request, "referate_creator_app/documents_list.html", {"documents": documents})


def upload_document(request):
    if request.method != "POST":
        return HttpResponseBadRequest("Некорректный метод запроса.")

    files = request.FILES.getlist("source_file")
    if not files:
        return HttpResponseBadRequest("Файлы не выбраны.")

    for f in files:
        # 1. Создаем объект (файл физически сохраняется в media/)
        document = Document.objects.create(
            title=os.path.splitext(f.name)[0],
            source_file=f,
        )

        try:
            # 2. Извлекаем текст
            text = extract_text_from_file(document.source_file.path)

            # Проверяем, не вернула ли функция текст ошибки из блока except
            if text.startswith("Ошибка при чтении файла:"):
                print(f"[Критическая ошибка]: {text}")
                document.text_content = "Ошибка обработки содержимого."
            elif not text.strip():
                print(f"[Предупреждение]: Файл {f.name} пуст или текст не распознан.")
                document.text_content = "Текст не найден (возможно, это скан/изображение)."
            else:
                document.text_content = text

            document.processed = True
            document.save()  # Обязательно сохраняем после обновления text_content

        except Exception as e:
            print(f"[Ошибка при извлечении текста из {f.name}]: {e}")
            document.text_content = f"Ошибка: {str(e)}"
            document.save()

    return redirect("documents_list")


def document_detail(request, doc_id):
    """Просмотр полного текста документа."""
    document = get_object_or_404(Document, id=doc_id)
    return render(request, "referate_creator_app/document_detail.html", {"document": document})


def select_documents(request):
    """Страница выбора документов для реферирования."""
    documents = Document.objects.all().order_by("-upload_date")

    if request.method == "POST":
        selected_ids = request.POST.getlist("documents")
        if not selected_ids:
            return redirect("select_documents")

        request.session['selected_doc_ids'] = [int(id) for id in selected_ids]
        return redirect("referencing_results")

    return render(request, "referate_creator_app/select_documents.html", {"documents": documents})


def referencing_results(request):
    """
    Основная логика: классический TF-IDF + Генерация ключевых слов через Ollama.
    """
    id_list = request.session.get('selected_doc_ids', [])

    if not id_list:
        return redirect("select_documents")

    documents = Document.objects.filter(id__in=id_list)
    results = []

    for doc in documents:
        text = doc.text_content or ""

        # --- 1. Классический реферат (TF-IDF) ---
        sentences_data, summary_sentences = generate_classic_summary(text, top_n=10)

        Sentence.objects.filter(document=doc).delete()
        for idx, (sent_text, weight) in enumerate(sentences_data):
            Sentence.objects.create(
                document=doc,
                text=sent_text,
                weight=weight,
                order_in_text=idx,
                selected_for_summary=(sent_text in summary_sentences)
            )

        summary_with_weights = [
            {'text': s, 'weight': w} for s, w in sentences_data if s in summary_sentences
        ]
        sorted_summary_for_display = sorted(summary_with_weights, key=lambda x: x['weight'], reverse=True)
        classic_summary_for_db = "\n".join(summary_sentences)

        # --- 2. Ключевые слова через Ollama (llama3) ---
        # Вызываем вашу функцию из ollama_client.py
        raw_keywords = generate_keywords_via_ollama(text)

        # Форматирование для красивого вывода в HTML
        formatted_lines = []
        for line in raw_keywords.splitlines():
            clean_line = line.strip()
            if not clean_line: continue

            # Если строка начинается с цифры (1. ) или * — это основной пункт
            if re.match(r'^(\d+\.|[*]|\d+\))', clean_line) or not line.startswith(' '):
                # Убираем лишние символы разметки для чистоты
                label = re.sub(r'^(\d+\.|[*]|\d+\))\s*', '', clean_line)
                formatted_lines.append(f"• {label}")
            # Если есть отступ или символ +, считаем вложенным
            else:
                label = clean_line.lstrip('+ ').strip()
                formatted_lines.append(f"  ◦ {label}")

        keywords_for_display = "\n".join(formatted_lines)

        # --- Сохранение в БД ---
        Summary.objects.update_or_create(
            document=doc,
            summary_type="classic",
            defaults={"content": classic_summary_for_db, "generation_method": "tfidf"}
        )
        Summary.objects.update_or_create(
            document=doc,
            summary_type="keywords",
            defaults={"content": raw_keywords, "generation_method": "ollama-llama3"}
        )

        results.append({
            "document": doc,
            "classic_summary_sorted": sorted_summary_for_display,
            "keywords_formatted": keywords_for_display,
        })

    return render(request, "referate_creator_app/referencing_results.html", {"results": results})


def generate_classic_summary(text: str, top_n: int = 10):
    """Метод Sentence Extraction + TF-IDF."""
    sentences = re.split(r'(?<=[.!?])\s+', text)
    if not sentences or not any(s.strip() for s in sentences):
        return [], []

    if len(sentences) <= 3:
        return [(s, 1.0) for s in sentences], sentences

    vectorizer = TfidfVectorizer(
        stop_words=list(RUSSIAN_STOPWORDS),
        lowercase=True,
        token_pattern=r"[a-zA-Zа-яА-ЯёЁ]+"
    )

    try:
        X = vectorizer.fit_transform(sentences)
        sentence_scores = np.asarray(X.sum(axis=1)).ravel()
        sentences_data = list(zip(sentences, sentence_scores))
        top_indices = sorted(np.argsort(sentence_scores)[-top_n:])
        summary_sentences = [sentences[i] for i in top_indices]
    except ValueError:
        summary_sentences = sentences[:top_n]
        sentences_data = [(s, 0.0) for s in sentences]

    return sentences_data, summary_sentences


def download_report(request):
    """Генерация HTML-файла для скачивания."""
    id_list = request.session.get('selected_doc_ids', [])
    if not id_list:
        return redirect("select_documents")

    documents = Document.objects.filter(id__in=id_list).prefetch_related('summaries')

    for doc in documents:
        doc.classic_summary_content = "Не сгенерировано"
        doc.keywords_summary_content = "Не сгенерировано"
        for summary in doc.summaries.all():
            if summary.summary_type == 'classic':
                doc.classic_summary_content = summary.content
            elif summary.summary_type == 'keywords':
                doc.keywords_summary_content = summary.content

    html_content = render_to_string('referate_creator_app/download_report.html', {'documents': documents})
    response = HttpResponse(html_content, content_type='text/html; charset=utf-8')
    response['Content-Disposition'] = 'attachment; filename="report.html"'
    return response


def history_list(request):
    """Отображение последних результатов из БД."""
    docs_with_history = Document.objects.filter(summaries__isnull=False).distinct()
    history_results = []

    for doc in docs_with_history:
        latest_classic = doc.summaries.filter(summary_type='classic').order_by('-created_at').first()
        latest_keywords = doc.summaries.filter(summary_type='keywords').order_by('-created_at').first()

        if not latest_classic or not latest_keywords:
            continue

        # Форматируем ключевые слова для истории
        fmt_k = []
        for line in latest_keywords.content.splitlines():
            line = line.strip()
            if line.startswith(('*', '+')):
                sym = '•' if line.startswith('*') else '  ◦'
                fmt_k.append(f"{sym} {line.strip('*+ ')}")
            elif line:
                fmt_k.append(f"• {line}")

        history_results.append({
            'document': doc,
            'classic_summary': latest_classic,
            'keywords_formatted': "\n".join(fmt_k),
        })

    history_results.sort(key=lambda x: x['classic_summary'].created_at, reverse=True)
    return render(request, 'referate_creator_app/history_list.html', {'history_results': history_results})


def help_page(request):
    """Страница справки."""
    return render(request, 'referate_creator_app/help_page.html')