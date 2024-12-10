from django.db import models


class Location(models.Model):
    name = models.CharField(max_length=255)

    def __str__(self):
        return self.name


# class WeatherLocation(models.Model):
#     name = models.CharField(max_length=255)
#     temperature = models.CharField(max_length=50)
#     condition = models.CharField(max_length=50)
#     # You can add more fields like latitude, longitude, etc.

#     def __str__(self):
#         return self.name