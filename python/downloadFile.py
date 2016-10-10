import requests

url = "https://upload.wikimedia.org/wikipedia/en/a/a9/Example.jpg"
response = requests.get(url)
if response.status_code == 200:
    f = open("example.jpg", 'wb')
    f.write(response.content)
    f.close()
