import pygame
import serial
import random
import time

# --- Seri Port Ayarlarý ---
SERIAL_PORT = "COM4"
BAUD_RATE = 9600

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.1)
    print(f"{SERIAL_PORT} portu açýldý.")
except:
    print(f"{SERIAL_PORT} portu açýlamadý!")
    ser = None

# --- Pygame Baþlat ---
pygame.init()

dis_width = 600
dis_height = 400
dis = pygame.display.set_mode((dis_width, dis_height))
pygame.display.set_caption('Joystick Kontrollü Yýlan Oyunu')

clock = pygame.time.Clock()

# Renkler (yumuþak pastel tonlar)
white = (245, 245, 245)
yellow = (255, 223, 100)
black = (30, 30, 30)
red = (220, 90, 90)
green = (100, 220, 100)
blue_start = (100, 150, 220)  # degrade baþlangýç
blue_end = (50, 90, 180)      # degrade bitiþ

snake_block = 15  # biraz daha büyük bloklar
snake_speed = 15

font_style = pygame.font.SysFont("bahnschrift", 25)
score_font = pygame.font.SysFont("comicsansms", 35, bold=True)

def draw_background():
    # Basit dikey degrade arka plan çizimi
    for i in range(dis_height):
        ratio = i / dis_height
        r = int(blue_start[0] * (1 - ratio) + blue_end[0] * ratio)
        g = int(blue_start[1] * (1 - ratio) + blue_end[1] * ratio)
        b = int(blue_start[2] * (1 - ratio) + blue_end[2] * ratio)
        pygame.draw.line(dis, (r, g, b), (0, i), (dis_width, i))

def Your_score(score):
    value = score_font.render("Skor: " + str(score), True, yellow)
    dis.blit(value, [10, 10])

def rounded_rect(surface, color, rect, radius=8):
    # Köþeleri yuvarlatýlmýþ dikdörtgen çizme fonksiyonu
    x, y, w, h = rect
    pygame.draw.rect(surface, color, (x + radius, y, w - 2*radius, h))
    pygame.draw.rect(surface, color, (x, y + radius, w, h - 2*radius))
    pygame.draw.circle(surface, color, (x + radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + w - radius, y + radius), radius)
    pygame.draw.circle(surface, color, (x + radius, y + h - radius), radius)
    pygame.draw.circle(surface, color, (x + w - radius, y + h - radius), radius)

def our_snake(snake_block, snake_list):
    for x in snake_list:
        # Yýlan parçalarýný hafif gölge efektiyle yuvarlatýlmýþ bloklar olarak çiz
        rounded_rect(dis, green, [x[0], x[1], snake_block, snake_block], radius=6)
        # Gölgeler için biraz daha koyu bir kenar çizimi (basit efekt)
        pygame.draw.rect(dis, (50, 150, 50), [x[0], x[1], snake_block, snake_block], 2, border_radius=6)

def message(msg, color, y_displace=0):
    # Mesaj kutusunu arka planý koyu, yarý saydam yapalým
    msg_surface = font_style.render(msg, True, color)
    box_w = msg_surface.get_width() + 40
    box_h = msg_surface.get_height() + 20
    box_x = dis_width / 2 - box_w / 2
    box_y = dis_height / 2 + y_displace - box_h / 2

    # Yarý saydam arka plan kutusu
    s = pygame.Surface((box_w, box_h), pygame.SRCALPHA)
    s.fill((30, 30, 30, 180))  # siyah yarý saydam
    dis.blit(s, (box_x, box_y))

    # Yazýyý kutunun üstüne çiz
    dis.blit(msg_surface, (dis_width / 2 - msg_surface.get_width() / 2, dis_height / 2 + y_displace - msg_surface.get_height() / 2))

def read_joystick_direction():
    if ser and ser.in_waiting > 0:
        try:
            line = ser.readline().decode('utf-8').strip()
            if line:
                x_str, y_str = line.split(',')
                x = int(x_str)
                y = int(y_str)

                center_x, center_y = 318, 326
                threshold_x = 150
                threshold_y = 150

                if x < center_x - threshold_x:
                    return "LEFT"
                elif x > center_x + threshold_x:
                    return "RIGHT"
                elif y > center_y + threshold_y:
                    return "UP"
                elif y < center_y - threshold_y:
                    return "DOWN"
        except:
            pass
    return None

def gameLoop():
    game_over = False
    game_close = False

    x1 = dis_width / 2
    y1 = dis_height / 2

    x1_change = 0
    y1_change = 0

    snake_List = []
    Length_of_snake = 1

    foodx = round(random.randrange(0, dis_width - snake_block) / 10.0) * 10.0
    foody = round(random.randrange(0, dis_height - snake_block) / 10.0) * 10.0

    score = 0

    while not game_over:

        while game_close:
            draw_background()
            message("Kaybettin! C - Çýkýþ, R - Tekrar Oyna", red)
            Your_score(score)
            pygame.display.update()

            for event in pygame.event.get():
                if event.type == pygame.KEYDOWN:
                    if event.key == pygame.K_c:
                        game_over = True
                        game_close = False
                    if event.key == pygame.K_r:
                        gameLoop()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                game_over = True
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT and x1_change == 0:
                    x1_change = -snake_block
                    y1_change = 0
                elif event.key == pygame.K_RIGHT and x1_change == 0:
                    x1_change = snake_block
                    y1_change = 0
                elif event.key == pygame.K_UP and y1_change == 0:
                    y1_change = -snake_block
                    x1_change = 0
                elif event.key == pygame.K_DOWN and y1_change == 0:
                    y1_change = snake_block
                    x1_change = 0

        joy_direction = read_joystick_direction()
        if joy_direction:
            if joy_direction == "LEFT" and x1_change == 0:
                x1_change = -snake_block
                y1_change = 0
            elif joy_direction == "RIGHT" and x1_change == 0:
                x1_change = snake_block
                y1_change = 0
            elif joy_direction == "UP" and y1_change == 0:
                y1_change = -snake_block
                x1_change = 0
            elif joy_direction == "DOWN" and y1_change == 0:
                y1_change = snake_block
                x1_change = 0

        if x1 >= dis_width or x1 < 0 or y1 >= dis_height or y1 < 0:
            game_close = True

        x1 += x1_change
        y1 += y1_change

        draw_background()
        # Yemeyi kare ve kýrmýzý yapalým
        pygame.draw.rect(dis, red, [foodx, foody, snake_block, snake_block])

        snake_Head = [x1, y1]
        snake_List.append(snake_Head)

        if len(snake_List) > Length_of_snake:
            del snake_List[0]

        for x in snake_List[:-1]:
            if x == snake_Head:
                game_close = True

        our_snake(snake_block, snake_List)
        Your_score(score)

        pygame.display.update()

        if x1 == foodx and y1 == foody:
            foodx = round(random.randrange(0, dis_width - snake_block) / 10.0) * 10.0
            foody = round(random.randrange(0, dis_height - snake_block) / 10.0) * 10.0
            Length_of_snake += 1
            score += 10

        clock.tick(snake_speed)

    pygame.quit()
    quit()

if __name__ == "__main__":
    gameLoop()
