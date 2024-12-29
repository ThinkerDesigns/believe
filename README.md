# Look Outsude

## Overview

This application provides real-time weather information, including current weather conditions, hourly forecasts, 5-day forecasts, and weather alerts. Users can input a city name to fetch weather data using the OpenWeatherMap API. The app supports temperature unit conversion between Celsius, Fahrenheit, and Kelvin. Additionally, it provides visual cues by displaying images corresponding to the temperature range.

## Features

- **Current Weather**: Displays temperature, humidity, pressure, and weather conditions for a given city.
- **Hourly Forecast**: Provides a detailed hourly forecast with temperatures and weather descriptions.
- **5-Day Forecast**: Shows the forecast for the next five days, including daily temperatures and weather descriptions.
- **Weather Alerts**: Displays any active weather alerts for the entered location.
- **Temperature Unit Conversion**: Toggle between Celsius (°C), Fahrenheit (°F), and Kelvin (K) for temperature units.
- **Temperature Images**: Displays images corresponding to the current temperature (cold, warm, good, or hot).

## Setup

1. **Install Required Libraries**: Ensure that your environment has the necessary Qt libraries installed for managing UI components, networking, and JSON parsing.
   
2. **API Key**: Obtain an API key from [OpenWeatherMap](https://openweathermap.org/api) and replace the placeholder `apiKey` in the code.

3. **Add Images**: The app uses images for temperature visualization. Add the following images to your resource file:
    - `cold.png` (for temperatures below 0°C)
    - `ok.png` (for temperatures between 0°C and 15°C)
    - `good.png` (for temperatures between 15°C and 25°C)
    - `hot.png` (for temperatures above 25°C)

## UI Components

- **Location Input**: A text input field for entering the city name.
- **Weather Button**: Fetches the weather data for the entered location.
- **Weather Label**: Displays the current weather data, including temperature and description.
- **Alert Label**: Shows any active weather alerts for the city.
- **Hourly Label**: Displays the hourly weather forecast.
- **5-Day Label**: Shows the 5-day weather forecast.
- **Unit Button**: Switches between Celsius, Fahrenheit, and Kelvin units for temperature display.
- **Temperature Image Label**: Displays images corresponding to the temperature range.

## Functionality

- **Fetching Weather Data**: The `onWeatherButtonClicked` method sends a request to the OpenWeatherMap API using the location entered by the user. The data is retrieved and displayed in the app's UI.

- **Handling Weather Data**: The `onWeatherDataReceived` method processes the weather data returned by the API, extracting details such as temperature, weather description, humidity, pressure, and other related information. It updates the UI with this data.

- **Temperature Unit Conversion**: The `onUnitButtonClicked` method allows the user to switch between Celsius, Fahrenheit, and Kelvin units. The displayed temperature adjusts accordingly.

- **Hourly and 5-Day Forecast**: The `parseHourlyForecast` and `parseFiveDayForecast` methods handle the parsing of hourly and 5-day forecast data from the API and update the respective UI elements.

- **Weather Alerts**: The `parseWeatherAlerts` method displays any weather alerts for the requested location.

## Usage

1. Enter a city name in the location input field.
2. Click the "Get Weather" button to fetch the current weather data and display it on the screen.
3. Use the unit button to toggle between Celsius, Fahrenheit, and Kelvin for temperature display.
4. View hourly and 5-day forecasts, as well as weather alerts, if available.
5. Temperature images will be updated according to the current temperature.

## Notes

- Ensure your OpenWeatherMap API key is valid and correctly inserted into the code.
- The temperature images are assigned based on predefined temperature ranges and are displayed to help visualize the current weather.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
