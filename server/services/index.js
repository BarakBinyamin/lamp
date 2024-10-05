const aedes = require('aedes')()

const g_mqttPort       = 8001
const g_websocketsPort = 8888

// Normal MQTT for IOT devices
const server = require('net').createServer(aedes.handle)
server.listen(g_mqttPort, function () {
  console.log('MQTT server listening on port ', g_mqttPort)
})

const express = require('express')
const app = express()

// ============================
// MQTT
const mqtt = require("mqtt");
const client = mqtt.connect(`mqtt://73.234.162.86:${g_mqttPort}`);

client.on("connect", () => {
  client.subscribe("arduino", err => {
    console.log("hee")
    if (!err) {
      console.log("subscribed")
    } else {
      console.log("error subscribing")
    }
  })
});

client.on("message", (topic, message) => {
  console.log(message.toString(), "TOPIC:", topic);
});

// ============================
// HTTP
app.get('/', (req, res) => {
  console.log("got it")
  client.publish("arduino", "some message");
  res.send('hello world')
})

app.listen(8000)
