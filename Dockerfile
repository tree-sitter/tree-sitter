FROM rust:1.90-trixie

WORKDIR /app

RUN apt-get update && apt-get install -y \
    clang \
    cmake \
    libclang-dev \
    nodejs \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN cargo xtask fetch-fixtures
RUN cargo xtask generate-fixtures

CMD ["cargo", "xtask", "test"]

