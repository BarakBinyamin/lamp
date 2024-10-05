'use strict'

const mqtt   = require('mqtt')
const client = mqtt.connect({ 
    port: 1883, 
    host: 'mbinyaminAdministrators-MacBook-Pro-2.local', 
    keepalive: 10000
});

// or const client = mqtt.connect({ port: 1883, host: '192.168.1.100', keepalive: 10000});
async function main(){
    client.subscribe('pico/topic')

    client.on('message', function (topic, message) {
        console.log(topic,":",message.toString())
    })
    client.publish('pico/topic', 'bin hier')
    await new Promise(res=>setTimeout(res,2000))
    client.end()
}

main()