# Stage 1: Download the tools needed
FROM archlinux:latest AS download
RUN pacman -Sy --noconfirm --needed base-devel gmp libmpc mpfr wget tar
WORKDIR /home
COPY scripts/download.sh .
RUN chmod +x ./download.sh
RUN ./download.sh
CMD ["sleep", "infinity"]

## Stage 2: Compile the cross compiler
FROM download AS build
WORKDIR /home
COPY scripts/crossCompiler.sh /home
RUN chmod +x ./crossCompiler.sh
RUN ./crossCompiler.sh
WORKDIR /home
COPY scripts/crossGcc.sh /home
RUN chmod +x ./crossGcc.sh
RUN ./crossGcc.sh
#ENTRYPOINT ["tail", "-f", "/dev/null"]
CMD ["sleep", "infinity"]

# Stage 3: Create a slim image with the cross-compiler
FROM archlinux:latest AS final
RUN pacman -Sy --noconfirm --needed base bash vim libisoburn mtools grub qemu-base
COPY --from=build /root/opt/cross /home/opt/cross
COPY --from=build /root/src/build-binutils /home/opt/binutils
COPY --from=build /root/src/build-gcc /home/opt/gcc
ENV PATH="/home/opt/binutils/bin:/home/opt/gcc/bin:/bin:/home/opt/cross/bin:$PATH"
WORKDIR /home
COPY ./inc ./inc
COPY ./src ./src
COPY ./scripts ./scripts

#RUN useradd -m -s /bin/bash developer
#USER developer
CMD ["sh", "/home/scripts/launch.sh"]
#ENTRYPOINT ["/bin/bash"]
