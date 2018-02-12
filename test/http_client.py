import requests

r = requests.post('http://127.0.0.1:8080', json={'key':'value2'})

print(r.status_code)