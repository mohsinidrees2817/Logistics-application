// server.js

const express = require('express');
const app = express();
const port = 8000; // You can change this to any port number you prefer

// // Define your API routes here
// // For example, a simple route to test if the server is running
// app.get('/api/test', (req, res) => {
//   res.json({ message: 'Server is running successfully!' });
// });

app.post('/api/placeOrder', (req, res) => {
    // Extract order details from the request body (assuming it's in JSON format)
    const { customerName, item, quantity } = req.body;
  
    // Call the corresponding C++ function to place the order
    const orderId = placeOrder(customerName, item, quantity);
  
    // Return the order ID in the response
    res.json({ orderId });
  });
  
  app.get('/api/orderStatus/:orderId', (req, res) => {
    // Extract the orderId from the URL parameters
    const orderId = req.params.orderId;
  
    // Call the corresponding C++ function to get the order status
    const orderStatus = getOrderStatus(orderId);
  
    // Return the order status in the response
    res.json({ orderId, orderStatus });
  });


// Start the server
app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
