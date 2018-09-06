#include <ST7920_I2C_MCP23017_GLCD.h>

ST7920_I2C_MCP23017_GLCD glcd;

static const uint16_t PROGMEM demo_bitmap[] = {
  0xFFFF, 0xFFE0, 0x07FF, 0xFF00, 0x1FFF, 0xFC3F, 0xFC00, 0x3FFF,
  0x7FFF, 0xFFF0, 0x0FFF, 0xFF80, 0x3FFF, 0xFE1F, 0xFC00, 0x3FFE,
  0x3FFF, 0xFFF8, 0x1FFF, 0xFFC0, 0x7FFF, 0xFF0F, 0xFC00, 0x3FFC,
  0x1FFF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFF00, 0xFFF8,
  0x0FFF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFF00, 0xFFF0,
  0x07FF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFF00, 0xFFE0,
  0x07FF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFFC3, 0xFFE0,
  0x07FF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFFC3, 0xFFE0,
  0x07FF, 0xFFFC, 0x3FFF, 0xFFE0, 0xFFFF, 0xFF87, 0xFFC3, 0xFFE0,
  0x07F8, 0x03FC, 0x3FC0, 0x1FE0, 0xFF00, 0x7F87, 0xFFE7, 0xFFE0,
  0x07F8, 0x03FC, 0x3FC0, 0x1FE0, 0xFF00, 0x7F87, 0xFFE7, 0xFFE0,
  0x07F8, 0x03FC, 0x3FC0, 0x1FE0, 0xFF00, 0x7F87, 0xFFE7, 0xFFE0,
  0x07F8, 0x03FC, 0x3FC0, 0x1FE0, 0xFF00, 0x7F87, 0xFFFF, 0xFFE0,
  0x07F8, 0x03FC, 0x3FC0, 0x1FE0, 0xFF00, 0x7F86, 0xFFFF, 0xFFE0,
  0x07F8, 0x03EC, 0x37C0, 0x1FE0, 0xFF00, 0x7D86, 0x7FFF, 0xFFE0,
  0x07F8, 0x03CC, 0x33C0, 0x1FE0, 0xFF00, 0x7986, 0x3FFF, 0xFFE0,
  0x07F8, 0x038C, 0x31C0, 0x1FE0, 0xFF00, 0x7186, 0x1FFF, 0xFFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1FFF, 0xFFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1BFF, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1BFF, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B7F, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B3F, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B1F, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B0F, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B07, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B03, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B01, 0xDFE0,
  0x07F8, 0x030C, 0x30C0, 0x1FE0, 0xFF00, 0x6186, 0x1B00, 0xDFE0,
  0x07F8, 0x030C, 0x3060, 0x1BE0, 0xFB00, 0xC186, 0x1BC3, 0xDFE0,
  0x07D8, 0x030C, 0x3030, 0x19E0, 0xF301, 0x8186, 0x18C3, 0xDFE0,
  0x0798, 0x060C, 0x3018, 0x18E0, 0xE303, 0x0186, 0x18C3, 0x1FE0,
  0x0718, 0x0C0C, 0x300C, 0x1860, 0xC306, 0x0186, 0x18C3, 0x1BE0,
  0x0618, 0x180C, 0x3006, 0x1860, 0xC30C, 0x0186, 0x18C3, 0x19E0,
  0x0618, 0x300C, 0x3003, 0x1860, 0xC318, 0x0186, 0x18E7, 0x18E0,
  0x0618, 0x600C, 0x3001, 0x9860, 0xC330, 0x0186, 0x18E7, 0x1860,
  0x0618, 0xC00C, 0x3000, 0xD860, 0xC360, 0x0186, 0x1824, 0x1860,
  0x0619, 0x800F, 0x1800, 0x7860, 0xC3C0, 0x031E, 0x1824, 0x1860,
  0x061B, 0x000E, 0x0C00, 0x3860, 0xC380, 0x060E, 0x1824, 0x1860,
  0x061E, 0x000C, 0x0600, 0x1860, 0xC300, 0x0C06, 0x183C, 0x1860,
  0x061C, 0x0018, 0x0300, 0x0860, 0xC200, 0x1803, 0x1818, 0x1860,
  0x0618, 0x0030, 0x0180, 0x0060, 0xC000, 0x3001, 0x9818, 0x1860,
  0x0610, 0x0060, 0x00C0, 0x00C0, 0x6000, 0x6000, 0xD818, 0x1860,
  0x0600, 0x00C0, 0x0060, 0x0180, 0x3000, 0xC000, 0x7800, 0x1860,
  0x0600, 0x0180, 0x0030, 0x0300, 0x1801, 0x8000, 0x3800, 0x1860,
  0x0600, 0x0300, 0x0018, 0x0600, 0x0C03, 0x0000, 0x1800, 0x1860,
  0x0600, 0x0600, 0x000C, 0x0C00, 0x0606, 0x0000, 0x0C00, 0x1860,
  0x0600, 0x0C00, 0x0006, 0x1800, 0x030C, 0x0000, 0x0600, 0x1860,
  0x0600, 0x1800, 0x0003, 0x3000, 0x0198, 0x0000, 0x0000, 0x1860,
  0x0600, 0x3000, 0x0001, 0xE000, 0x00F0, 0x0000, 0x0000, 0x1860,
  0x0600, 0x6000, 0x0000, 0xC000, 0x0060, 0x0000, 0x0000, 0x1860,
  0x0600, 0xC000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1860,
  0x0601, 0x8000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1860,
  0x0603, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1860,
  0x0606, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1860,
  0x060C, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x7860,
  0x0618, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x3860,
  0x0630, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1860,
  0x0660, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0C60,
  0x06C0, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0660,
  0x0780, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0360,
  0x0700, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x01E0,
  0x0600, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x00E0,
  0x0C00, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0060,
  0x1800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0030 
}; 

void setup() {
  glcd.set_inverse(true);
  glcd.set_rotate_180(true);
  glcd.init_display();
}

void loop() {
  glcd.draw_line(0, 0, 127, 63);
  glcd.draw_line(127, 0, 0, 63);
  delay(15000);
  glcd.clear_screen();
  glcd.draw_triangle(32, 1, 1, 62, 62, 62);
  glcd.draw_filled_triangle(96, 1, 65, 62, 126, 62);
  delay(15000);
  glcd.clear_screen();
  glcd.draw_frame(1, 1, 62, 62);
  glcd.draw_box(65, 1, 62, 62);
  delay(15000);
  glcd.clear_screen();
  glcd.draw_rounded_frame(1, 1, 62, 62, 10);
  glcd.draw_filled_rounded_box(65, 1, 62, 62, 10);
  delay(15000);
  glcd.clear_screen();
  glcd.draw_circle(32, 32, 31);
  glcd.draw_filled_circle(96, 32, 31);
  delay(15000);
  glcd.clear_screen();
  glcd.draw_ellipse(32, 16, 62, 30);
  glcd.draw_filled_ellipse(96, 48, 62, 30);
  delay(15000);
  glcd.clear_screen();
  glcd.write_string("Hello World) Not to try make long string");
  ///glcd.set_cursour(20, 1);
  glcd.write_string("Сообщение на русском");
  delay(15000);
  glcd.clear_screen();
  draw_plot();
  delay(15000);
  glcd.clear_screen();
  glcd.draw_bitmap(demo_bitmap, 128, 64);
  delay(15000);
  glcd.clear_screen();
}

void draw_plot() {
  glcd.write_char_x_y(4, 59, 0);
  glcd.write_gnumber_x_y(113, 59, 100);
  glcd.write_char_x_y(0, 0, 9);
  glcd.write_char_x_y(0, 53, 0);
  glcd.draw_line(4, 57, 128, 57);
  glcd.draw_line(4, 0, 4, 57);
  int k = 32;
  for (int i = 5; i < 128; i++) {
    int j = rand() % 3;
    glcd.draw_pixel(i, k);
    if (j == 1) {
      k--;
    }
    if (j > 1) {
      k++;
    }
  }
}