<<<<<<< HEAD
FROM ubuntu:latest
MAINTAINER Rajdeep Dua "dua_rajdeep@yahoo.com"
RUN apt-get update -y
RUN apt-get install -y python-pip python-dev build-essential
COPY . /app
WORKDIR /app
RUN pip install -r requirements.txt
ENTRYPOINT ["python"]
CMD ["app.py"]
=======
FROM python:2.7         
ADD . /todo
WORKDIR /todo
EXPOSE 5000
RUN pip install -r requirements.txt
ENTRYPOINT ["python", "app.py"]
>>>>>>> 7997471b89df127fb63efbf6b5ba2917f6b8ddd4
