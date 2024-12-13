import os
from langchain.document_loaders import PyPDFLoader
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain.embeddings import HuggingFaceEmbeddings
from langchain.vectorstores import FAISS
from pdf2image import convert_from_path
import pytesseract


class PDFProcessor:
    def __init__(self, model_name="jhgan/ko-sroberta-multitask"):
        self.model_name = model_name

    def is_image_based_pdf(self, pdf_path):
        try:
            loader = PyPDFLoader(pdf_path)
            documents = loader.load()
            if documents and any(doc.page_content.strip() for doc in documents):
                return False
        except Exception:
            pass
        return True

    def extract_text_from_image_pdf(self, pdf_path):
        images = convert_from_path(pdf_path)
        text = ""
        for image in images:
            text += pytesseract.image_to_string(image, lang="kor")
        return text

    def split_text_into_chunks(self, documents, chunk_size=500, chunk_overlap=50):
        splitter = RecursiveCharacterTextSplitter(chunk_size=chunk_size, chunk_overlap=chunk_overlap)
        return splitter.split_documents(documents)

    def process_pdf(self, pdf_path):
        if self.is_image_based_pdf(pdf_path):
            extracted_text = self.extract_text_from_image_pdf(pdf_path)
            documents = [{"page_content": extracted_text}]
        else:
            loader = PyPDFLoader(pdf_path)
            documents = loader.load()
        return self.split_text_into_chunks(documents)

    def process_all_pdfs_in_directory(self, directory):
        vector_store = None
        for file_name in os.listdir(directory):
            if file_name.endswith(".pdf"):
                pdf_path = os.path.join(directory, file_name)
                chunks = self.process_pdf(pdf_path)

                embeddings = HuggingFaceEmbeddings(model_name=self.model_name)
                if vector_store is None:
                    vector_store = FAISS.from_documents(chunks, embeddings)
                else:
                    vector_store.add_documents(chunks)
        return vector_store

    def count_pages(self, pdf_path):
        try:
            images = convert_from_path(pdf_path)
            return len(images)
        except Exception:
            return 0

    def get_pdf_summary(self, pdf_path):
        chunks = self.process_pdf(pdf_path)
        return {"file": pdf_path, "chunks": len(chunks), "page_count": self.count_pages(pdf_path)}
