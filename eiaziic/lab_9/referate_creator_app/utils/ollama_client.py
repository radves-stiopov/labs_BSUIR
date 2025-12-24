import requests
import json


def generate_keywords_via_ollama(doc_text: str, max_chars: int = 8000) -> str:
    if len(doc_text) > max_chars:
        doc_text = doc_text[:max_chars] + "..."

    # Усиленный промпт для соблюдения языкового режима
    prompt = f"""
Ты — профессиональный лингвист и аналитик. 
Твоя задача: проанализировать текст и составить иерархический список ключевых слов.

СТРОГИЕ ПРАВИЛА:
1. ЯЗЫК: Если текст на русском, то ВЕСЬ ответ должен быть только на русском языке.Если текст на английском, то  ВЕСЬ ответ должен быть только на английском языке.
2. ФОРМАТ: Только список. Никаких вводных слов.
3. СТРУКТУРА: 
   * Главная тема
     + Подтема или уточнение
4. Только термины, никаких предложений.

Текст для анализа:
\"\"\"{doc_text}\"\"\"
"""

    url = "http://localhost:11434/api/chat"
    payload = {
        "model": "llama3",
        "messages": [
            {"role": "user", "content": prompt}
        ],
        "stream": False,
        "options": {
            "temperature": 0.1,  # Еще ниже для максимальной точности
            "top_p": 0.9
        }
    }

    try:
        response = requests.post(url, json=payload, timeout=120)
        response.raise_for_status()
        data = response.json()

        if "message" in data:
            content = data["message"]["content"].strip()

            # Очистка: убираем возможные фразы "Вот список:" если они просочились
            lines = content.splitlines()
            valid_lines = []
            for line in lines:
                clean = line.strip()
                if clean.startswith(('*', '+', '-', '•')):
                    valid_lines.append(line)  # Сохраняем оригинал с отступами

            return "\n".join(valid_lines) if valid_lines else content

        return "Ошибка: пустой ответ от модели"

    except Exception as e:
        return f"Ошибка Ollama: {str(e)}"