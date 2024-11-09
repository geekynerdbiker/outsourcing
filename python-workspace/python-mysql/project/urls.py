"""
URL configuration for project project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.urls import path
from .views import UserRegistrationSerializer, UserLoginSerializer, DiaryCreateAPIView, DiaryListAPIView, \
    DiaryUpdateAPIView, DiaryDeleteAPIView

urlpatterns = [
    path('api/register/', UserRegistrationSerializer.as_view(), name='user-register'),
    path('api/login/', UserLoginSerializer.as_view(), name='user-login'),
    path('api/diaries/create/', DiaryCreateAPIView.as_view(), name='diary-create'),
    path('api/diaries/list/', DiaryListAPIView.as_view(), name='diary-list'),
    path('api/diaries/<int:pk>/update/', DiaryUpdateAPIView.as_view(), name='diary-update'),
    path('api/diaries/<int:pk>/delete/', DiaryDeleteAPIView.as_view(), name='diary-delete'),
]
