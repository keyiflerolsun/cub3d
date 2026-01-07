# 🎮 cub3D

42 İstanbul için hazırlanan **cub3D** projesi, Wolfenstein 3D tarzında bir 3D oyun motorudur. Bu proje, raycasting tekniğini kullanarak 2D haritadan 3D perspektif görünümü oluşturur.

---

## 📚 İçindekiler

- [Kurulum](#-kurulum)
- [Kullanım](#-kullanım)
- [Proje Yapısı](#-proje-yapısı)
- [Parser Modülü](#-parser-modülü)
- [Game Modülü](#-game-modülü)
- [Harita Dosyası Formatı](#-harita-dosyası-formatı)
- [Kontroller](#-kontroller)
- [Teknik Detaylar](#-teknik-detaylar)

---

## 🛠 Kurulum

```bash
# Projeyi derlemek için:
make

# Temizlemek için:
make clean    # Object dosyalarını siler
make fclean   # Tüm derlenmiş dosyaları siler
make re       # Temiz derleme yapar
```

### Bağımlılıklar
- **MiniLibX**: X11 grafik kütüphanesi (otomatik olarak indirilir)
- **libft**: 42 standart kütüphane fonksiyonları
- **ft_printf**: Özel printf implementasyonu
- **get_next_line**: Satır okuma fonksiyonu

---

## 🎯 Kullanım

```bash
./cub3d maps/ex.cub
```

---

## 📁 Proje Yapısı

```
cub3d/
├── main.c                  # Ana giriş noktası ve event handler'lar
├── cub3d.h                 # Ana header dosyası ve struct tanımları
├── Makefile                # Derleme kuralları
│
├── src/
│   ├── parser/             # Harita ayrıştırma modülü
│   │   ├── parser.h
│   │   ├── read_map.c
│   │   ├── validate_map.c
│   │   ├── validate_textures.c
│   │   ├── parse_texture.c
│   │   ├── parse_color.c
│   │   ├── parse_number.c
│   │   ├── flood_fill.c
│   │   ├── map_utils.c
│   │   ├── map_borders.c
│   │   └── utils.c
│   │
│   └── game/               # Oyun mantığı modülü
│       ├── game.h
│       ├── draw.c
│       ├── paint.c
│       ├── player.c
│       ├── image.c
│       └── print_game_info.c
│
├── maps/                   # Harita dosyaları
│   └── ex.cub
│
├── textures/               # Doku dosyaları (.xpm)
│
├── libft/                  # Libft kütüphanesi
├── ft_printf/              # ft_printf kütüphanesi
├── get_next_line/          # GNL kütüphanesi
└── minilibx-linux/         # MiniLibX grafik kütüphanesi
```

---

## 🔍 Parser Modülü

Parser modülü, `.cub` harita dosyasını okur, doğrular ve oyun yapısına yükler.

### Akış Diyagramı

```
.cub dosyası → read_map() → read_headers() → parse_config_line()
                                                    ↓
                        ┌─────────────────────────────────────────┐
                        │  parse_textures() → NO, SO, WE, EA      │
                        │  parse_color()    → F, C (RGB)          │
                        └─────────────────────────────────────────┘
                                                    ↓
                         read_map_data() → Harita satırlarını oku
                                                    ↓
                         ft_split() → 2D karakter dizisine dönüştür
                                                    ↓
                         validate_map() → Harita doğrulama
                                                    ↓
                    ┌───────────────────────────────────────────────┐
                    │  • Geçerli karakterler: 0, 1, N, S, E, W, ' ' │
                    │  • Tek oyuncu kontrolü                        │
                    │  • validate_textures() → Dosya var mı?        │
                    │  • fill_check() → Harita kapalı mı?           │
                    └───────────────────────────────────────────────┘
```

### Dosya Açıklamaları

| Dosya | Açıklama |
|-------|----------|
| `read_map.c` | Ana harita okuma fonksiyonu. Dosyayı açar, header'ları (texture + color) okur, harita verisini alır |
| `parse_texture.c` | `NO`, `SO`, `WE`, `EA` texture yollarını ayrıştırır |
| `parse_color.c` | `F` (floor) ve `C` (ceiling) RGB değerlerini ayrıştırır, format doğrulaması yapar |
| `parse_number.c` | RGB değerleri için sayı parse eder |
| `validate_map.c` | Harita karakterlerini kontrol eder, oyuncu pozisyonunu bulur, satır/sütun sayısını hesaplar |
| `validate_textures.c` | Texture dosyalarının var olup olmadığını kontrol eder |
| `flood_fill.c` | Oyuncu pozisyonundan başlayarak haritanın kapalı olup olmadığını kontrol eder |
| `map_utils.c` | Harita yardımcı fonksiyonları (karakter doğrulama, bellek yönetimi) |
| `map_borders.c` | Harita sınır kontrolü |
| `utils.c` | Genel yardımcı fonksiyonlar (`err_exit`, `skip_spaces`) |

### Flood Fill Algoritması

Haritanın duvarlarla çevrili olup olmadığını kontrol eden önemli bir algoritma:

```c
int fill_map(t_game *g, char **map, int r, int c)
{
    // Harita dışına çıkıldıysa → HATA
    if (r < 0 || r >= rows || c < 0 || c >= columns)
        return (0);
    
    // Duvar veya ziyaret edilmişse → OK
    if (map[r][c] == '1' || map[r][c] == '*')
        return (1);
    
    // Boşluk karakterine ulaşıldıysa → HATA (kapalı değil)
    if (map[r][c] == ' ')
        return (0);
    
    // Ziyaret edildi olarak işaretle
    map[r][c] = '*';
    
    // Dört yöne de recursive olarak devam et
    return fill_map(r+1, c) && fill_map(r-1, c) 
        && fill_map(r, c+1) && fill_map(r, c-1);
}
```

---

## 🎮 Game Modülü

Game modülü, raycasting ile 3D render, oyuncu hareketi ve texture mapping işlemlerini yönetir.

### Oyun Döngüsü

```
main()
    │
    ├── read_map()          # Parser haritayı yükler
    ├── mlx_init()          # MiniLibX başlatılır
    ├── mlx_new_window()    # Pencere oluşturulur
    ├── mlx_new_image()     # Çizim buffer'ı oluşturulur
    ├── key_hooks()         # Event handler'lar bağlanır
    │
    └── mlx_loop() ──→ draw_loop() [her frame]
                            │
                            ├── move_player()     # Hareket ve rotasyon
                            ├── clear_image()     # Buffer'ı temizle
                            │
                            ├── for x in 0..WIDTH:
                            │       │
                            │       ├── calculate ray angle
                            │       ├── get_dda_dist()    # DDA raycasting
                            │       ├── calc_texture_x()  # Hangi texture?
                            │       └── draw_pixels()     # Sütunu çiz
                            │
                            └── mlx_put_image_to_window()
```

### Dosya Açıklamaları

| Dosya | Açıklama |
|-------|----------|
| `draw.c` | Ana raycasting mantığı. DDA algoritması ile duvar mesafesi hesaplar |
| `paint.c` | Piksel çizimi, texture renk alma, texture seçimi |
| `player.c` | Oyuncu hareketi (WASD), rotasyon (← →), çarpışma kontrolü |
| `image.c` | Düşük seviye piksel işlemleri (`put_pixel`, `clear_image`, `rgb_to_hex`) |
| `print_game_info.c` | Oyuncu ve texture başlatma, debug bilgileri |

### Raycasting (DDA Algoritması)

```
Oyuncu pozisyonundan ekranın her sütunu için bir ışın gönderilir:

       ┌──────────────────────────────────┐
       │  Oyuncu (P)                      │
       │       ↘↓↙                        │
       │  Işınlar yayılır (FOV: 60°)      │
       │                                  │
       │      ▓▓▓ Duvar                   │
       └──────────────────────────────────┘

1. Her ışın için başlangıç açısı hesaplanır
2. DDA ile ışın grid boyunca ilerletilir
3. Duvarla çarpışma mesafesi hesaplanır
4. Mesafeye göre duvar yüksekliği belirlenir
5. Texture mapping yapılır ve sütun çizilir
```

### DDA (Digital Differential Analyzer)

```c
// Işın ilerleme mantığı
while (!hit_wall)
{
    if (side_x < side_y)
    {
        side_x += delta_x;   // X yönünde ilerle
        map_x += step_x;
        side = 0;            // Dikey duvar
    }
    else
    {
        side_y += delta_y;   // Y yönünde ilerle  
        map_y += step_y;
        side = 1;            // Yatay duvar
    }
    
    if (map[map_y][map_x] == '1')
        hit_wall = true;
}
```

### Texture Seçimi

Işının duvara çarpış yönüne göre texture belirlenir:

| Koşul | Texture |
|-------|---------|
| `side == 0` ve `step_x > 0` | Doğu (East) duvarı |
| `side == 0` ve `step_x < 0` | Batı (West) duvarı |
| `side == 1` ve `step_y > 0` | Güney (South) duvarı |
| `side == 1` ve `step_y < 0` | Kuzey (North) duvarı |

---

## 📄 Harita Dosyası Formatı

`.cub` dosyaları aşağıdaki yapıda olmalıdır:

```
NO ./textures/north_wall.xpm    # Kuzey duvar texture'ı
SO ./textures/south_wall.xpm    # Güney duvar texture'ı
WE ./textures/west_wall.xpm     # Batı duvar texture'ı
EA ./textures/east_wall.xpm     # Doğu duvar texture'ı

F 220,100,0                      # Zemin rengi (R,G,B)
C 50,50,120                      # Tavan rengi (R,G,B)

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Geçerli Harita Karakterleri

| Karakter | Anlamı |
|----------|--------|
| `0` | Yürünebilir alan |
| `1` | Duvar |
| `N` | Oyuncu başlangıç pozisyonu (Kuzeye bakıyor) |
| `S` | Oyuncu başlangıç pozisyonu (Güneye bakıyor) |
| `E` | Oyuncu başlangıç pozisyonu (Doğuya bakıyor) |
| `W` | Oyuncu başlangıç pozisyonu (Batıya bakıyor) |
| ` ` | Boşluk (harita dışı alan) |

### Harita Kuralları

1. ✅ Harita duvarlarla (`1`) tamamen çevrili olmalıdır
2. ✅ Tam olarak **bir** oyuncu başlangıç pozisyonu olmalıdır
3. ✅ Tüm texture dosyaları mevcut olmalıdır
4. ✅ RGB değerleri 0-255 arasında olmalıdır
5. ✅ Dosya uzantısı `.cub` olmalıdır

---

## 🎹 Kontroller

| Tuş | İşlev |
|-----|-------|
| `W` | İleri git |
| `S` | Geri git |
| `A` | Sola strafe |
| `D` | Sağa strafe |
| `←` | Sola dön |
| `→` | Sağa dön |
| `ESC` / `Q` | Oyundan çık |

---

## ⚙️ Teknik Detaylar

### Sabitler (`cub3d.h`)

| Sabit | Değer | Açıklama |
|-------|-------|----------|
| `WIDTH` | 1920 | Ekran genişliği (piksel) |
| `HEIGHT` | 1080 | Ekran yüksekliği (piksel) |
| `BLOCK_SIZE` | 64 | Harita grid boyutu |
| `P` | 3.14159... | Pi sayısı |
| `FOV` | 60° | Görüş açısı |

### Veri Yapıları

```c
typedef struct s_game
{
    void        *mlx;           // MiniLibX bağlantısı
    void        *win;           // Pencere pointer'ı
    void        *img;           // Çizim buffer'ı
    t_map       map;            // Harita verisi
    t_player    player;         // Oyuncu durumu
    t_texture   texture;        // Texture yolları
    t_color     floor;          // Zemin rengi
    t_color     ceiling;        // Tavan rengi
    t_img       north_wall;     // Yüklü texture'lar
    t_img       south_wall;
    t_img       east_wall;
    t_img       west_wall;
}               t_game;

typedef struct s_player
{
    float   x, y;               // Piksel pozisyonu
    float   rotation;           // Bakış açısı (radyan)
    int     key_up, key_down;   // Hareket durumları
    int     key_left, key_right;
    int     rotate_left, rotate_right;
    int     speed;              // Hareket hızı
    float   angle_speed;        // Dönüş hızı
}               t_player;
```

---

## 👥 Yazarlar

- **hyakici** - [@hyakici](https://github.com/halitykc)
- **osancak** - [@osancak](https://github.com/keyiflerolsun)

---

## 📝 Lisans

Bu proje 42 İstanbul eğitim programı kapsamında geliştirilmiştir.

---

<div align="center">
  <img src="https://img.shields.io/badge/42-cub3D-blue?style=for-the-badge" alt="42 cub3D">
</div>
