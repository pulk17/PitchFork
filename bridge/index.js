const net = require('net');
const WebSocket = require('ws');
const fs = require('fs');

const wss = new WebSocket.Server({ port: 8080 });

const SOCKET_PATH = '/tmp/orderbook.sock';

if (fs.existsSync(SOCKET_PATH)) fs.unlinkSync(SOCKET_PATH);

const server = net.createServer((socket) => {
    console.log('C++ engine connected'); 
    socket.on('data', (chunk) => {
        console.log('data received, bytes:', chunk.length);
        wss.clients.forEach((client) => {
            if (client.readyState === WebSocket.OPEN) {
                client.send(chunk.toString());
            }
        });
    });
});

server.listen(SOCKET_PATH, () => {
    console.log(`Server listening on ${SOCKET_PATH}`);
});