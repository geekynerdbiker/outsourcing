import tkinter as tk
from tkinter import scrolledtext
from pdf_processor import PDFProcessor
from chatbot import Chatbot
import os

HUGGINGFACE_API_KEY = "api_key"

pdf_directory = "./pdfs"
pdf_processor = PDFProcessor()
if os.path.exists(pdf_directory):
    chat_log_content = "PDF 파일을 불러오고 처리 중입니다...\n"
    vector_store = pdf_processor.process_all_pdfs_in_directory(pdf_directory)
    chat_log_content += "PDF 파일이 성공적으로 처리되었습니다.\n"
else:
    vector_store = None
    chat_log_content = f"경로 {pdf_directory}가 존재하지 않습니다. 디렉토리를 생성하고 PDF 파일을 추가하세요.\n"

chatbot = Chatbot(vector_store, huggingface_api_key=HUGGINGFACE_API_KEY)


def ask_question():
    """사용자의 질문을 처리하고 응답을 출력합니다."""
    question = user_input.get()
    if question and vector_store:
        answer = chatbot.get_answer(question)
        chat_log.insert(tk.END, f"사용자: {question}\n")
        chat_log.insert(tk.END, f"챗봇: {answer}\n")
    else:
        chat_log.insert(tk.END, "PDF 파일이 올바르게 로드되지 않았습니다. 프로그램을 다시 시작하세요.\n")


def show_statistics():
    """문서 통계를 출력합니다."""
    if vector_store:
        stats = chatbot.document_statistics()
        chat_log.insert(tk.END, f"문서 통계: {stats}\n")
    else:
        chat_log.insert(tk.END, "로드된 문서가 없습니다.\n")


app = tk.Tk()
app.title("대학교 정보 챗봇")
app.geometry("700x500")

chat_log = scrolledtext.ScrolledText(app, wrap=tk.WORD, state="normal", width=80, height=25)
chat_log.pack(pady=10)

chat_log.insert(tk.END, chat_log_content)

user_input = tk.Entry(app, width=70)
user_input.pack(pady=5)

button_frame = tk.Frame(app)
button_frame.pack()

ask_button = tk.Button(button_frame, text="질문하기", command=ask_question)
ask_button.grid(row=0, column=0, padx=5)

stats_button = tk.Button(button_frame, text="문서 통계 보기", command=show_statistics)
stats_button.grid(row=0, column=1, padx=5)

app.mainloop()
