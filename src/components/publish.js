import mqtt from "mqtt";

function mqttConnect(host, mqttOption) {
  return mqtt.connect(host, mqttOption);
}

  var client = "";
  const host = "broker.hivemq.com";
  const clientId = `mqttjs_ + ${Math.random().toString(16).substr(2, 8)}`;
  const port = 8000;

  const username = "user";
  const password = "pass";
  const topic = "topic098651";
  const url = `ws://${host}:${port}/mqtt`;
  const options = {
    keepalive: 30,
    protocolId: "MQTT",
    protocolVersion: 4,
    clean: true,
    reconnectPeriod: 1000,
    connectTimeout: 30 * 1000,
    will: {
      topic: "WillMsg",
      payload: "Connection Closed abnormally..!",
      qos: 0,
      retain: false,
    },
    rejectUnauthorized: false,
  };
  options.clientId = clientId;
  options.username = username;
  options.password = password;
  const tempClient = mqttConnect(url, options);
  client = tempClient;
  // var mqtt    = require('mqtt');
  // var client  = mqtt.connect('mqtt://broker.hivemq.com',{
  //   port: 8000,
  // });

  // var topic = "topic098651";
  // var message = "this shows up if you run publishtest.js";
const publish = function(payload) {
  
  if (client) {
    client.publish(topic, payload, 1, (error) => {
      if (error) {
        console.log("Publish error: ", error);
      }
    });
  }


  // client.on("connect", ()=>{
  //     client.publish(topic, message);
  //     console.log("msg");
  // }) 
}

export default publish;