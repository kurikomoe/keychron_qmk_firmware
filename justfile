clean:
    rm -rf ./keychron_k6_pro_ansi_rgb_via_logger.bin

cfg:
    qmk generate-compilation-database  -kb keychron/k6_pro/ansi/rgb -km via_logger

build: clean cfg
    qmk compile  -kb keychron/k6_pro/ansi/rgb -km via_logger -j 24
