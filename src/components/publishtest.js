var mqtt    = require('mqtt');
var client  = mqtt.connect('mqtt://broker.hivemq.com',{
  port: 1883
});

var topic = "topic098651";
var message = "this shows up if you run publishtest.js";

client.on("connect", ()=>{
    client.publish(topic, message);
    console.log("msg");
}) 