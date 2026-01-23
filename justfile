cfg:
    qmk generate-compilation-database  -kb keychron/k6_pro/ansi/rgb -km via_logger

build: cfg
    qmk compile  -kb keychron/k6_pro/ansi/rgb -km via_logger
