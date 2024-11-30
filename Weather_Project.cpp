#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include <list>

using namespace std;

// Class definitions (as provided earlier)

// Forward declarations for associations
class Location;
class WeatherData;
class Alert;
class Notification;
class APIService;
class UserPreferences;

// Class Definitions
class User {
public:
    int userID;
    string name;
    string email;
    map<string, string> preferences;
    vector<Location> savedLocations;
    vector<Notification> notifications;
    UserPreferences* userPreferences;

    User(int id, string name, string email)
        : userID(id), name(name), email(email), userPreferences(nullptr) {}

    bool registerUser(string email, string password) {
        cout << "User registered with email: " << email << endl;
        return true;
    }

    bool login(string email, string password) {
        cout << "User logged in with email: " << email << endl;
        return true;
    }

    void updatePreferences(map<string, string> newPreferences) {
        preferences = newPreferences;
        cout << "Preferences updated successfully!" << endl;
    }
};

class Location {
public:
    int locationID;
    string name;
    double latitude;
    double longitude;
    WeatherData* weatherData;

    Location(int id, string name, double lat, double lon)
        : locationID(id), name(name), latitude(lat), longitude(lon), weatherData(nullptr) {}

    map<string, string> getLocationData() {
        map<string, string> data = {
            {"Name", name},
            {"Latitude", to_string(latitude)},
            {"Longitude", to_string(longitude)}
        };
        return data;
    }

    void saveLocation(string locName, double lat, double lon) {
        name = locName;
        latitude = lat;
        longitude = lon;
        cout << "Location saved: " << locName << endl;
    }
};

class WeatherData {
public:
    float temperature;
    int humidity;
    float windSpeed;
    int uvIndex;
    int airQualityIndex;
    vector<Alert> alerts;

    WeatherData(float temp, int hum, float wind, int uv, int airQuality)
        : temperature(temp), humidity(hum), windSpeed(wind), uvIndex(uv), airQualityIndex(airQuality) {}

    map<string, string> fetchCurrentWeather(int locationID) {
        map<string, string> weather = {
            {"Temperature", to_string(temperature)},
            {"Humidity", to_string(humidity)},
            {"WindSpeed", to_string(windSpeed)}
        };
        return weather;
    }

    list<map<string, string>> fetchForecast(int locationID) {
        // Dummy forecast data
        list<map<string, string>> forecast = {
            {{"Day", "Monday"}, {"Temperature", "25"}},
            {{"Day", "Tuesday"}, {"Temperature", "28"}}
        };
        return forecast;
    }
};

class Notification {
public:
    int notificationID;
    string type;
    string message;
    time_t timestamp;

    Notification(int id, string t, string msg)
        : notificationID(id), type(t), message(msg) {
        timestamp = time(nullptr);
    }

    void sendNotification(int userID, string msg) {
        cout << "Notification sent to User " << userID << ": " << msg << endl;
    }

    void setAlert(int userID, string alertType, double threshold) {
        cout << "Alert set for User " << userID << " for " << alertType << " with threshold " << threshold << endl;
    }
};

class APIService {
public:
    string apiKey;
    string endpointURL;

    APIService(string key, string url) : apiKey(key), endpointURL(url) {}

    string fetchData(string endpoint, map<string, string> params) {
        cout << "Fetching data from " << endpoint << "..." << endl;
        return "{ \"data\": \"sample JSON data\" }";
    }

    map<string, string> parseData(string json) {
        map<string, string> parsedData = {
            {"Key", "Value"}
        };
        return parsedData;
    }
};

class UserPreferences {
public:
    string units;
    string language;
    map<string, string> alertSettings;

    UserPreferences(string u, string lang)
        : units(u), language(lang) {}

    void updatePreferences(string u, string lang, map<string, string> alerts) {
        units = u;
        language = lang;
        alertSettings = alerts;
        cout << "Preferences updated: " << units << ", " << language << endl;
    }

    map<string, string> getPreferences() {
        return {
            {"Units", units},
            {"Language", language}
        };
    }
};

class Alert {
public:
    int alertID;
    string alertType;
    string alertMessage;
    string severity;

    Alert(int id, string type, string msg, string sev)
        : alertID(id), alertType(type), alertMessage(msg), severity(sev) {}

    bool triggerAlert(int locationID, string type) {
        cout << "Triggered alert for Location " << locationID << ": " << type << endl;
        return true;
    }
};

// Main function
int main() {
    // Create a user
    User user1(1, "John Doe", "john.doe@example.com");
    user1.registerUser("john.doe@example.com", "password123");

    // Add a location
    Location loc1(1, "New York", 40.7128, -74.0060);
    loc1.saveLocation("New York", 40.7128, -74.0060);

    // Update user preferences
    map<string, string> prefs = {{"units", "Celsius"}, {"language", "en"}};
    user1.updatePreferences(prefs);

    // Create a WeatherData object and fetch weather data
    WeatherData weather(25.5, 60, 15.0, 5, 50);
    auto currentWeather = weather.fetchCurrentWeather(loc1.locationID);
    cout << "Current Weather" << endl;
    for (const auto& entry : currentWeather) {
        cout << entry.first << ": " << entry.second << endl;
    }

    // Create and send a notification
    Notification notif(1, "Weather Alert", "Severe Storm Warning");
    notif.sendNotification(user1.userID, "Severe Storm Warning");

    return 0;
}