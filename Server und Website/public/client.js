let temperatures = []
let xs = [0]

function getAndUpdateTemperature() {
    fetch("http://4.180.5.111:3000/temperature")
        .then(res => res.json())
        .then((temperatureJson) => {
            temperatures.push(temperatureJson["temperature"]);
            updateTemperatureField(temperatureJson["temperature"]);
        });
}

function updateTemperatureField(temperature) {
    document.getElementById("Temperaturanzeige").textContent = "Temperatur: " + temperature;

    temperatureGraph = document.getElementById("Temperaturgraph");
    Plotly.newPlot(temperatureGraph, [{
        x: xs,
        y: temperatures
    }], {
        margin: { t: 0 }
    });

    xs.push(xs[xs.length - 1] + 1);
}

window.onload = (event) => {
    setInterval(getAndUpdateTemperature, 1000);
}