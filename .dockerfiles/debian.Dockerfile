FROM debian:trixie-slim

RUN apt-get update && apt-get install -y build-essential valgrind libcriterion-dev bear

ARG USER_ID
ARG USER=nonroot
ARG HOME=/workdir

# create non-privileged user
# (https://runbook.academy/courses/linux/lessons/linux-service-and-system-accounts/)
RUN useradd -u ${USER_ID} -U --system --home-dir ${HOME} --create-home -s /usr/sbin/nologin ${USER}
USER ${USER}

WORKDIR ${HOME}
ENTRYPOINT ["/usr/bin/bash", "-c"]
