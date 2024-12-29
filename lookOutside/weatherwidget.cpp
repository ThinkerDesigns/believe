#include "weatherwidget.h"
#include "ui_weatherwidget.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QVBoxLayout>

WeatherWidget::WeatherWidget(QWidget *parent)
    : QWidget(parent),
    locationInput(new QLineEdit(this)),
    weatherLabel(new QLabel(this)),
    alertLabel(new QLabel(this)),
    hourlyLabel(new QLabel(this)),
    fiveDayLabel(new QLabel(this)),
    weatherButton(new QPushButton("Get Weather", this)),
    unitButton(new QPushButton("Switch to °F", this)),
    networkManager(new QNetworkAccessManager(this)),
    temperatureImageLabel(new QLabel(this)) {  // Initialize the image label
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Add input and button
    layout->addWidget(locationInput);
    layout->addWidget(weatherButton);

    // Add main weather label
    layout->addWidget(weatherLabel);

    // Add new widgets for alerts, hourly, and 5-day forecasts
    layout->addWidget(alertLabel);
    layout->addWidget(hourlyLabel);
    layout->addWidget(fiveDayLabel);

    // Add unit switcher
    layout->addWidget(unitButton);

    // Add the label for displaying temperature images
    layout->addWidget(temperatureImageLabel);

    // Set the layout to the widget
    setLayout(layout);

    locationInput->setPlaceholderText("Enter the city");
    alertLabel->setStyleSheet("color: red; font-size: 14px; font-weight: bold;");
    hourlyLabel->setStyleSheet("color: blue; font-size: 14px;");
    fiveDayLabel->setStyleSheet("color: green; font-size: 14px;");
    alertLabel->setVisible(true);
    hourlyLabel->setVisible(true);
    fiveDayLabel->setVisible(true);
    connect(weatherButton, &QPushButton::clicked, this, &WeatherWidget::onWeatherButtonClicked);
    connect(networkManager, &QNetworkAccessManager::finished, this, &WeatherWidget::onWeatherDataReceived);
    connect(unitButton, &QPushButton::clicked, this, &WeatherWidget::onUnitButtonClicked);
}



WeatherWidget::~WeatherWidget() {}

void WeatherWidget::onWeatherButtonClicked() {
    QString location = locationInput->text();
    if (location.isEmpty()) {
        weatherLabel->setText("Please enter a location.");
        return;
    }

    // Correct API endpoint
    QUrl url("https://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;
    query.addQueryItem("q", location);
    query.addQueryItem("appid", apiKey);  // Replace `apiKey` with your actual key
    query.addQueryItem("units", currentUnit == "C" ? "metric" : "imperial");
    url.setQuery(query);

    networkManager->get(QNetworkRequest(url));
}


void WeatherWidget::onWeatherDataReceived(QNetworkReply *reply) {
    if (reply->error()) {
        weatherLabel->setText("Failed to retrieve weather data.");
    } else {
        QByteArray responseData = reply->readAll();
        qDebug() << "API Response:" << responseData; // Debugging: Print API response
        QJsonDocument doc = QJsonDocument::fromJson(responseData);
        QJsonObject jsonObject = doc.object();

        if (jsonObject.contains("weather") && jsonObject.contains("main")) {
            // Parse weather data
            QString description = jsonObject["weather"].toArray().first().toObject()["description"].toString();
            double temp = jsonObject["main"].toObject()["temp"].toDouble();
            double feelsLike = jsonObject["main"].toObject()["feels_like"].toDouble();
            double minTemp = jsonObject["main"].toObject()["temp_min"].toDouble();
            double maxTemp = jsonObject["main"].toObject()["temp_max"].toDouble();
            double humidity = jsonObject["main"].toObject()["humidity"].toDouble();
            double pressure = jsonObject["main"].toObject()["pressure"].toDouble();
            QString cityName = jsonObject["name"].toString();

            // Display weather data
            weatherLabel->setText(QString("Weather in %1:\nDescription: %2\nTemperature: %3°C\nFeels Like: %4°C\nMin Temp: %5°C\nMax Temp: %6°C\nHumidity: %7%%\nPressure: %8 hPa")
                                      .arg(cityName)
                                      .arg(description)
                                      .arg(temp)
                                      .arg(feelsLike)
                                      .arg(minTemp)
                                      .arg(maxTemp)
                                      .arg(humidity)
                                      .arg(pressure));

            // Check the temperature range and set the corresponding image
            if (temp < 0) {
                temperatureImageLabel->setPixmap(QPixmap(":/images/cold.png"));
            } else if (temp >= 0 && temp <= 15) {
                temperatureImageLabel->setPixmap(QPixmap(":/images/ok.png"));
            } else if (temp > 15 && temp <= 25) {
                temperatureImageLabel->setPixmap(QPixmap(":/images/good.png"));
            } else if (temp > 25) {
                temperatureImageLabel->setPixmap(QPixmap(":/images/hot.png"));
            }
        } else {
            weatherLabel->setText("Invalid location or data unavailable.");
        }
    }
    reply->deleteLater();
}

void WeatherWidget::onUnitButtonClicked() {
    if (currentUnit == "C") {
        currentUnit = "F";
        unitButton->setText("Switch to K");
    } else if (currentUnit == "F") {
        currentUnit = "K";
        unitButton->setText("Switch to °C");
    } else {
        currentUnit = "C";
        unitButton->setText("Switch to °F");
    }
    updateWeatherLabel();
}

void WeatherWidget::updateWeatherLabel() {
    double tempInUnit = convertTemperature(currentTemp, currentUnit);
    QString unitSymbol = (currentUnit == "C") ? "°C" : (currentUnit == "F") ? "°F" : "K";
    weatherLabel->setText(QString("Weather: %1\nTemperature: %2%3")
                              .arg(currentDescription, QString::number(tempInUnit), unitSymbol));
}

double WeatherWidget::convertTemperature(double temp, const QString &unit) {
    if (unit == "F") {
        return temp * 9.0 / 5.0 + 32;  // Convert Celsius to Fahrenheit
    } else if (unit == "K") {
        return temp + 273.15;  // Convert Celsius to Kelvin
    } else {
        return temp;  // Return Celsius as is
    }
}

void WeatherWidget::parseHourlyForecast(const QJsonArray &hourlyData) {
    QString hourlyText = "Hourly Forecast:\n";
    for (const QJsonValue &value : hourlyData) {
        QJsonObject hourObject = value.toObject();
        double temp = hourObject["temp"].toDouble();
        QString description = hourObject["weather"].toArray().first().toObject()["description"].toString();
        hourlyText += QString("Temp: %1°C, Description: %2\n").arg(temp).arg(description);
        qDebug() << "Parsed Hourly Data:" << "Temp:" << temp << "Description:" << description;
    }
    hourlyLabel->setText(hourlyText);
}



void WeatherWidget::parseFiveDayForecast(const QJsonArray &dailyData) {
    QString dailyText = "5-Day Forecast:\n";
    for (const QJsonValue &value : dailyData) {
        QJsonObject dayObject = value.toObject();
        double tempDay = dayObject["temp"].toObject()["day"].toDouble();
        QString description = dayObject["weather"].toArray().first().toObject()["description"].toString();
        dailyText += QString("Day Temp: %1°C, Description: %2\n").arg(tempDay).arg(description);
        qDebug() << "Parsed Daily Data:" << "Day Temp:" << tempDay << "Description:" << description;
    }
    fiveDayLabel->setText(dailyText);
}


void WeatherWidget::parseWeatherAlerts(const QJsonArray &alertsData) {
    QString alertText = "Alerts:\n";
    for (const QJsonValue &value : alertsData) {
        QJsonObject alertObject = value.toObject();
        QString sender = alertObject["sender_name"].toString();
        QString event = alertObject["event"].toString();
        QString description = alertObject["description"].toString();
        alertText += QString("Sender: %1\nEvent: %2\nDescription: %3\n\n").arg(sender, event, description);
        qDebug() << "Parsed Alert Data:" << "Sender:" << sender << "Event:" << event << "Description:" << description;
    }
    alertLabel->setText(alertText);
}

