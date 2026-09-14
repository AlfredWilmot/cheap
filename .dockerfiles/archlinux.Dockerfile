FROM archlinux/archlinux:base-devel-20260913.0.593083

# generate pacman keys to enable system update and package installation via pacman
# (https://hub.docker.com/r/archlinux/archlinux)
RUN pacman-key --init && pacman-key --populate archlinux

# install updates and system deps (bear -> generate compilation db; criterion -> unit-test harness),
# and remove old packages/cache-dir
RUN pacman -Suy --noconfirm bear criterion valgrind && pacman -Scc --noconfirm

# create non-privileged user
# (https://runbook.academy/courses/linux/lessons/linux-service-and-system-accounts/)
ARG USER_ID

# NOTE: env-var necessary for memcheck to work (https://bbs.archlinux.org/viewtopic.php?id=276422)
ENV DEBUGINFOD_URLS="https://debuginfod.archlinux.org"

RUN useradd -u ${USER_ID} -U --system --home-dir /workdir --create-home -s /usr/sbin/nologin nonroot

WORKDIR /workdir
USER nonroot
ENTRYPOINT ["/usr/bin/bash"]
