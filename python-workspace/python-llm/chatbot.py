from langchain.chains import RetrievalQA
from langchain.llms import HuggingFaceHub
from huggingface_hub import login


class Chatbot:
    def __init__(self, vector_store, repo_id="google/flan-t5-base", huggingface_api_key=None):
        self.vector_store = vector_store
        self.repo_id = repo_id
        self.huggingface_api_key = huggingface_api_key

        if self.huggingface_api_key:
            login(token=self.huggingface_api_key)

    def initialize_qa_chain(self):
        retriever = self.vector_store.as_retriever()
        llm = HuggingFaceHub(
            repo_id=self.repo_id,
            model_kwargs={"temperature": 0.5, "max_length": 256},
        )
        return RetrievalQA(llm=llm, retriever=retriever)

    def get_answer(self, question):
        qa_chain = self.initialize_qa_chain()
        return qa_chain.run(question)

    def test_retrieval(self, query, top_k=3):
        retriever = self.vector_store.as_retriever()
        docs = retriever.get_relevant_documents(query)[:top_k]
        return [doc.page_content for doc in docs]

    def list_all_documents(self):
        return self.vector_store.store.keys()

    def document_statistics(self):
        retriever = self.vector_store.as_retriever()
        docs = retriever.get_all_documents()
        return {"total_documents": len(docs), "unique_chunks": len(set(docs))}
