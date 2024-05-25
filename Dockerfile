FROM --platform=linux/amd64 ubuntu:20.04

RUN apt-get update \
   && DEBIAN_FRONTEND=noninteractive apt-get install -y \
   curl \
   git \
   make \
   cmake \
   vim \
   wget \
   gcc \
   gdb \
   valgrind \
   mpich \
   libpng-dev \
   python3 \
   python3-pip \
   python3-matplotlib \
   python3-numpy \
   && apt-get clean \
   && rm -rf /var/lib/apt/lists/* \
   && update-alternatives --install /usr/bin/python python /usr/bin/python3 1

RUN pip install jupyter jupyterlab jupyter_contrib_nbextensions
ENV JUPYTER_ENABLE_LAB=yes
CMD ["jupyter", "lab", "--ip=0.0.0.0", "--port=8888", "--allow-root", "--no-browser", "--ServerApp.token=''", "--ServerApp.password=''", "--ServerApp.allow_origin='*'", "--ServerApp.disable_check_xsrf=True", "--ServerApp.allow_root=True", "--ServerApp.open_browser=False"]
EXPOSE 8888

# CMD ["tail", "-f", "/dev/null"]
