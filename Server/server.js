const express = require('express');

const app = express();
app.use(express.static('public'));
app.use(express.json());

const port = 3000;

let temperature = 0;

app.get('/', (req, res) => {
    res.send('Hello World!');
});

app.post(('/temperature'), (req, res) => {
    // Parsed by json middleware
    console.log(req.body);
    temperature = req.body.temperature;
});

app.get('/temperature', (req, res) => {
    console.log(`GET request to /temperature, sending ${temperature}`);
    res.send({
        "temperature": temperature
    })
});

app.listen(port, () => {
    console.log(`App listening on port ${port}`);
});
