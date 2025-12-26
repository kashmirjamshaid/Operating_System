import express from 'express';
import mongoose from 'mongoose';
import cors from 'cors';
const app = express();
const PORT = 3000;
app.use(cors());
app.use(express.json());
// MongoDB connection URL
const MONGO_URL = process.env.MONGO_URL ||
    'mongodb://mongodb:27017/guestbook';
// Define Mongoose Schema
const messageSchema = new mongoose.Schema({
    name: {
        type: String,
        required: true
    },
    message: {
        type: String,
        required: true
    },
    timestamp: {
        type: Date,
        default: Date.now
    }
});
// Create Mongoose Model
const Message = mongoose.model('Message', messageSchema);
// Connect to MongoDB
async function connectDB() {
    try {
        await mongoose.connect(MONGO_URL);
        console.log('Connected to MongoDB with Mongoose');
    } catch (error) {
        console.error('MongoDB connection error:', error);
        process.exit(1);
    }
}
// Get all messages
app.get('/api/messages', async (req, res) => {
    try {
        const messages = await Message.find()
            .sort({ timestamp: -1 })
            .limit(10);
        res.json(messages);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
// Post a new message
app.post('/api/messages', async (req, res) => {
    try {
        const { name, message } = req.body;
        const newMessage = new Message({
            name,
            message
        });
        await newMessage.save();
        res.status(201).json(newMessage);
    } catch (error) {
        res.status(400).json({ error: error.message });
    }
});
// Start server
connectDB().then(() => {
    app.listen(PORT, () => {
        console.log(`Server running on port ${PORT}`);
    });
});