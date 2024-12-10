from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from django.contrib.auth.forms import AuthenticationForm
from django.contrib.auth import login, logout, authenticate
from .forms import CustomUserCreationForm
from .forms import UpdateEmailForm
from django.contrib import messages

def register(request):

    if request.user.is_authenticated:
        return redirect('home')
    
    if request.method == 'POST':
        form = CustomUserCreationForm(request.POST)
        if form.is_valid():
            form.save()
            messages.success(request, "Registration successful. You can now log in.")
            return redirect('login')
    else:
        form = CustomUserCreationForm()
    return render(request, 'register.html', {'form': form})

def login_view(request):

    if request.user.is_authenticated:
        return redirect('home')
    
    if request.method == 'POST':
        form = AuthenticationForm(data=request.POST)
        if form.is_valid():
            user = form.get_user()
            login(request, user)
            messages.success(request, f"Welcome, {user.username}!")
            return redirect('home')
        else:
            messages.error(request, "Invalid username or password.")
    else:
        form = AuthenticationForm()
    return render(request, 'login.html', {'form': form})



def logout_view(request):
    logout(request)
    messages.success(request, "You have been logged out.")
    return redirect('login')



@login_required
def updateemail(request):
    user = request.user
    if request.method == 'POST':
        form = UpdateEmailForm(request.POST, instance=user)
        if form.is_valid():
            form.save()
            messages.success(request, "Your email has been updated successfully!")
            return redirect('settings')  # Redirect to a profile or another relevant page
        else:
            messages.error(request, "Please correct the error below.")
    else:
        form = UpdateEmailForm(instance=user)
    return render(request, 'update_email.html', {'form': form})







# @login_required(login_url='login/')
def home(request):
    
    if request.user.is_authenticated:
        return render(request, 'home.html')
    else:
        return render(request, 'home.html')
        # return redirect('login')
        


def welcome(request):

    if request.user.is_authenticated:
        return redirect('home')
    else:
        return render(request, 'welcome.html')


# @login_required
def settings(request):
    if request.user.is_authenticated:
        return render(request, 'settings.html')
    else:
        return render(request, 'settings.html', {'user': request.user})


def aqi(request):
    return render(request, 'aqi.html')

def weather(request):
    return render(request, 'weather.html')


def notifications(request):
    return render(request, 'notifications.html')

# def savedlocations(request):

#     locations = Location.objects.all()
    
#     return render(request, 'savedlocations.html', {'locations': locations})


def savedlocations(request):
    # Get all saved weather locations from the database
    locations = Location.objects.all()
    
    if request.method == 'POST':
        # Get the ID of the location to delete
        location_id = request.POST.get('location_id')
        if location_id:
            # Delete the location with the given ID
            Location.objects.filter(id=location_id).delete()
            return redirect('savedlocations')  # Redirect to refresh the page
    
    return render(request, 'savedlocations.html', {'locations': locations, 'user': request.user})


from django.shortcuts import render
from django.contrib.auth.decorators import login_required

@login_required
def user_profile(request):
    # Fetch the logged-in user's data
    user = request.user
    return render(request, 'user_profile.html', {'user': user})


from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from .models import Location  # Assuming you have a Location model
import json

@csrf_exempt
def add_location(request):
    if request.method == "POST":
        try:
            data = json.loads(request.body)
            location_name = data.get("location")

            # Add the location to the database
            Location.objects.create(name=location_name)

            return JsonResponse({"message": "Location added successfully!"}, status=200)
        except Exception as e:
            return JsonResponse({"error": str(e)}, status=400)
    return JsonResponse({"error": "Invalid request method."}, status=405)


