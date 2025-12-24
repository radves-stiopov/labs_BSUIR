import pypdf

def extract_text_from_file(file_path: str) -> str:
    """Извлекает текст из PDF-файла, удаляя пустые строки."""
    # Проверка расширения файла


    text_content = []

    try:
        with open(file_path, "rb") as f:
            reader = pypdf.PdfReader(f)

            # Перебор всех страниц документа
            for page in reader.pages:
                page_text = page.extract_text()

                if page_text:
                    # Разбиваем текст на строки, очищаем их и убираем пустые
                    lines = [line.strip() for line in page_text.splitlines() if line.strip()]
                    text_content.extend(lines)

    except Exception as e:
        return f"Ошибка при чтении файла: {e}"

    return "\n".join(text_content)