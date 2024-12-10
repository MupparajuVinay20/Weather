from django.urls import path
from . import views

urlpatterns = [
    path('', views.welcome, name='welcome'),
    path('register/', views.register, name='register'),
    path('login/', views.login_view, name='login'),
    path('logout/', views.logout_view, name='logout'),
    path('home/', views.home, name='home'),
    path('updateemail/', views.updateemail, name='updateemail'),
    path('aqi/', views.aqi, name='aqi'),
    path('weather/', views.weather, name='weather'),
    path('savedlocations/', views.savedlocations, name='savedlocations'),
    path('notifications/', views.notifications, name='notifications'),
    path('settings/', views.settings, name='settings'),
    path('add-location/', views.add_location, name='add_location'),
]
