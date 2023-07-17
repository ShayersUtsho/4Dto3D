import pygame
from math import sin, cos

pygame.init()
WINDOW_SIZE = (400, 400)
screen = pygame.display.set_mode(WINDOW_SIZE)

player = [[10.0, 10.0], (0, 0, 0)]

level = []
for i in range(20):
    line = []
    for j in range(20):
        if j == 0 or j == 19 or i == 0 or i == 19:
            if i % 2 == 1 and j % 2 == 0:
                line.append((200, 200, 30))
            elif i % 2 == 1 or j % 2 == 0:
                line.append((200, 30, 30))
            else:
                line.append((30, 30, 200))
        else:
            line.append((255, 255, 255))

    level.append(line)

# Update the display
pygame.display.flip()

# Wait for the user to close the window
done = False
left = False
right = False
up = False
down = False
strafe_left = False
strafe_right = False

wall_color = (0, 0, 0)
player_angle = 0.0
fov = 3.1415 / 2
while not done:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_a:
            left = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_d:
            right = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_w:
            up = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_s:
            down = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_q:
            strafe_left = True
        if event.type == pygame.KEYDOWN and event.key == pygame.K_e:
            strafe_right = True

        if event.type == pygame.KEYUP and event.key == pygame.K_a:
            left = False
        if event.type == pygame.KEYUP and event.key == pygame.K_d:
            right = False
        if event.type == pygame.KEYUP and event.key == pygame.K_w:
            up = False
        if event.type == pygame.KEYUP and event.key == pygame.K_s:
            down = False
        if event.type == pygame.KEYUP and event.key == pygame.K_q:
            strafe_left = False
        if event.type == pygame.KEYUP and event.key == pygame.K_e:
            strafe_right = False

    if left:
        player_angle -= 60
    if right:
        player_angle += 60
    if up:
        player[0][0] += cos(player_angle/360)
        player[0][1] += sin(player_angle/360)
    if down:
        player[0][0] -= cos(player_angle/360)
        player[0][1] -= sin(player_angle/360)
    if strafe_left:
        player[0][0] -= cos(player_angle+3.1415/2)
        player[0][1] -= sin(player_angle+3.1415/2)
    if strafe_right:
        player[0][0] += cos(player_angle+3.1415/2)
        player[0][1] += sin(player_angle+3.1415/2)
    print(player_angle)

    for x in range(400):
        eye_angle = (player_angle + x - 200) * fov / 400

        testX = player[0][0]
        testY = player[0][1]
        hit_wall = False
        wall_distance = 0
        while not hit_wall:
            if level[int(testX)][int(testY)] != (255, 255, 255):
                hit_wall = True
                wall_color = level[int(testX)][int(testY)]
                break
            else:
                testX += cos(eye_angle)
                testY += sin(eye_angle)
                wall_distance += 1
        for y in range(400):
            if y < wall_distance * 10 or 399 - wall_distance * 10 < y:
                screen.set_at((x, y), (0, 0, 0))
            else:
                screen.set_at((x, y), wall_color)
    pygame.display.flip()

# Quit Pygame
pygame.quit()
