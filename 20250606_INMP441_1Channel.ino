#include <driver/i2s.h>

#define I2S_WS 25
#define I2S_SD 22
#define I2S_SCK 26
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 1024

void setup() {
  Serial.begin(115200);

  // Cấu hình I2S cho INMP441
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD
  };

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pin_config);
  i2s_zero_dma_buffer(I2S_NUM_0);
}

void loop() {
  const int samples = 1024;
  int32_t buffers[samples];
  size_t bytes_read;

  i2s_read(I2S_NUM_0, &buffers, sizeof(buffers), &bytes_read, portMAX_DELAY);

  for (int i = 0; i < samples; i++) {
    Serial.println(buffers[i]);
  }
}
