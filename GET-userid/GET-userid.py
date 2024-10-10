from datetime import datetime
from flask import Flask, request, abort
import requests
import json

app = Flask(__name__)

@app.route('/', methods=['POST', 'GET'])
def webhook():
    if request.method == 'POST':
        payload = request.json
        reply_token = payload['events'][0]['replyToken']
        timestamp = payload['events'][0]['timestamp']
        user_id = payload['events'][0]['source']['userId']  # Extract user ID

        # Check the timestamp
        current_time = datetime.now().timestamp() * 1000  # Convert to milliseconds
        time_difference = current_time - timestamp
        print(f'Timestamp difference: {time_difference} ms')

        print(f'Reply token: {reply_token}')
        print(f'User ID: {user_id}')

        # Initialize reply_message_status
        reply_message_status = None

        # Check if 'message' key exists in the payload
        if 'message' in payload['events'][0]:
            message = payload['events'][0]['message']['text']
            print(f'Message: {message}')

            if reply_message_status == 200:
                return 'OK', 200
            else:
                return 'Error', 500

        else:
            # Handle the case where 'message' key is missing
            abort(400)

if __name__ == '__main__':
    app.run(debug=True)