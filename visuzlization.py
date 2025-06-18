import pygame
import random
import time
from pygame.locals import *

# Initialize Pygame
pygame.init()

# Constants
WIDTH, HEIGHT = 900, 600
UI_HEIGHT = 180
BAR_AREA_HEIGHT = HEIGHT - UI_HEIGHT

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (180, 180, 180)
RED = (255, 0, 0)
GREEN = (0, 200, 0)
BLUE = (0, 0, 255)
CONTROL_PANEL_COLOR = (240, 240, 240)

# Setup
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Sorting Algorithm Visualizer")
clock = pygame.time.Clock()

# Fonts
FONT = pygame.font.SysFont("Arial", 20)
FONT_TITLE = pygame.font.SysFont("Arial", 22, bold=True)

# Default values
data_size = 38
min_val = 0
max_val = 10
delay = 0.15
sorting = False
algorithms = ["Bubble Sort", "Selection Sort", "Merge Sort", "Quick Sort"]
current_algorithm = "Merge Sort"
data = []
sort_gen = None
highlight_indices = []

# Generate random data
def generate_data():
    global data
    data = [random.randint(min_val, max_val) for _ in range(data_size)]

# Sorting algorithms
def bubble_sort(data):
    n = len(data)
    for i in range(n):
        for j in range(0, n-i-1):
            if data[j] > data[j+1]:
                data[j], data[j+1] = data[j+1], data[j]
                yield j, j+1
        yield -1, -1

def selection_sort(data):
    for i in range(len(data)):
        min_idx = i
        for j in range(i+1, len(data)):
            if data[j] < data[min_idx]:
                min_idx = j
            yield i, j
        data[i], data[min_idx] = data[min_idx], data[i]
        yield i, min_idx

def merge_sort(data):
    def merge_sort_recursive(start, end):
        if end - start > 1:
            mid = (start + end) // 2
            yield from merge_sort_recursive(start, mid)
            yield from merge_sort_recursive(mid, end)
            left = data[start:mid]
            right = data[mid:end]
            i = j = 0
            for k in range(start, end):
                if i < len(left) and (j >= len(right) or left[i] <= right[j]):
                    data[k] = left[i]
                    i += 1
                else:
                    data[k] = right[j]
                    j += 1
                yield k, -1
    yield from merge_sort_recursive(0, len(data))

def quick_sort(data):
    def quick_sort_recursive(start, end):
        if start >= end:
            return
        pivot = data[end]
        i = start
        for j in range(start, end):
            if data[j] < pivot:
                data[i], data[j] = data[j], data[i]
                i += 1
            yield i, j
        data[i], data[end] = data[end], data[i]
        yield i, end
        yield from quick_sort_recursive(start, i-1)
        yield from quick_sort_recursive(i+1, end)
    yield from quick_sort_recursive(0, len(data)-1)

# UI Elements
class Button:
    def __init__(self, x, y, width, height, text, color, text_color=BLACK):
        self.rect = pygame.Rect(x, y, width, height)
        self.text = text
        self.color = color
        self.text_color = text_color
        self.hover_color = (min(color[0]+30, 255), min(color[1]+30, 255), min(color[2]+30, 255))

    def draw(self, surface):
        mouse_pos = pygame.mouse.get_pos()
        current_color = self.hover_color if self.rect.collidepoint(mouse_pos) else self.color
        pygame.draw.rect(surface, current_color, self.rect, border_radius=4)
        pygame.draw.rect(surface, BLACK, self.rect, 1, border_radius=4)
        text_surf = FONT.render(self.text, True, self.text_color)
        text_rect = text_surf.get_rect(center=self.rect.center)
        surface.blit(text_surf, text_rect)

    def is_clicked(self, pos, event):
        return event.type == MOUSEBUTTONDOWN and event.button == 1 and self.rect.collidepoint(pos)

class Dropdown:
    def __init__(self, x, y, width, height, options, initial_option):
        self.rect = pygame.Rect(x, y, width, height)
        self.options = options
        self.selected = initial_option
        self.active = False

    def draw(self, surface):
        pygame.draw.rect(surface, WHITE, self.rect)
        pygame.draw.rect(surface, BLACK, self.rect, 1)
        text_surf = FONT.render(self.selected, True, BLACK)
        surface.blit(text_surf, (self.rect.x + 10, self.rect.y + 5))
        arrow = [(self.rect.right - 15, self.rect.y + 10), (self.rect.right - 5, self.rect.y + 10), (self.rect.right - 10, self.rect.y + 20)]
        pygame.draw.polygon(surface, BLACK, arrow)
        if self.active:
            for i, option in enumerate(self.options):
                option_rect = pygame.Rect(self.rect.x, self.rect.y + (i+1) * self.rect.height, self.rect.width, self.rect.height)
                pygame.draw.rect(surface, WHITE, option_rect)
                pygame.draw.rect(surface, BLACK, option_rect, 1)
                option_surf = FONT.render(option, True, BLACK)
                surface.blit(option_surf, (option_rect.x + 10, option_rect.y + 5))

    def handle_event(self, event):
        if event.type == MOUSEBUTTONDOWN:
            if self.rect.collidepoint(event.pos):
                self.active = not self.active
            else:
                for i, option in enumerate(self.options):
                    option_rect = pygame.Rect(self.rect.x, self.rect.y + (i+1) * self.rect.height, self.rect.width, self.rect.height)
                    if option_rect.collidepoint(event.pos):
                        self.selected = option
                        self.active = False
                        return True
                self.active = False
        return False

class InputBox:
    def __init__(self, x, y, width, height, text=''):
        self.rect = pygame.Rect(x, y, width, height)
        self.color = BLACK
        self.text = text
        self.txt_surface = FONT.render(text, True, self.color)
        self.active = False

    def handle_event(self, event):
        if event.type == MOUSEBUTTONDOWN:
            self.active = self.rect.collidepoint(event.pos)
            self.color = RED if self.active else BLACK
        if event.type == pygame.KEYDOWN and self.active:
            if event.key == pygame.K_RETURN:
                return True
            elif event.key == pygame.K_BACKSPACE:
                self.text = self.text[:-1]
            elif event.unicode.isdigit() or event.unicode == '.':
                self.text += event.unicode
            self.txt_surface = FONT.render(self.text, True, self.color)
        return False

    def draw(self, screen):
        screen.blit(self.txt_surface, (self.rect.x+5, self.rect.y+5))
        pygame.draw.rect(screen, self.color, self.rect, 2)

    def get_value(self):
        try:
            return float(self.text) if '.' in self.text else int(self.text)
        except ValueError:
            return 0

# Create UI Elements
algorithm_dropdown = Dropdown(350, 20, 200, 40, algorithms, current_algorithm)
data_size_input = InputBox(130, 80, 80, 30, str(data_size))
min_input = InputBox(330, 80, 80, 30, str(min_val))
max_input = InputBox(530, 80, 80, 30, str(max_val))
speed_input = InputBox(730, 80, 80, 30, str(delay))
start_button = Button(300, 130, 120, 40, "Start", GREEN)
generate_button = Button(500, 130, 120, 40, "Generate", GRAY)

# Initial data
generate_data()

# Main loop
running = True
while running:
    for event in pygame.event.get():
        if event.type == QUIT:
            running = False

        if algorithm_dropdown.handle_event(event):
            current_algorithm = algorithm_dropdown.selected

        if start_button.is_clicked(pygame.mouse.get_pos(), event) and not sorting:
            sorting = True
            if current_algorithm == "Bubble Sort":
                sort_gen = bubble_sort(data)
            elif current_algorithm == "Selection Sort":
                sort_gen = selection_sort(data)
            elif current_algorithm == "Merge Sort":
                sort_gen = merge_sort(data)
            elif current_algorithm == "Quick Sort":
                sort_gen = quick_sort(data)

        if generate_button.is_clicked(pygame.mouse.get_pos(), event):
            data_size = data_size_input.get_value()
            min_val = min_input.get_value()
            max_val = max_input.get_value()
            delay = speed_input.get_value()
            generate_data()
            sorting = False

        for box in [data_size_input, min_input, max_input, speed_input]:
            box.handle_event(event)

    # Sorting Step
    if sorting and sort_gen:
        try:
            highlight_indices = next(sort_gen)
            if isinstance(highlight_indices, int):
                highlight_indices = (highlight_indices, -1)
            time.sleep(delay)
        except StopIteration:
            sorting = False
            highlight_indices = (-1, -1)

    # Draw everything
    screen.fill(WHITE)
    pygame.draw.rect(screen, CONTROL_PANEL_COLOR, (0, 0, WIDTH, UI_HEIGHT))

    # Titles and labels
    screen.blit(FONT_TITLE.render("Algorithm:", True, BLACK), (250, 30))
    algorithm_dropdown.draw(screen)

    screen.blit(FONT_TITLE.render("Parameters:", True, BLACK), (30, 55))
    screen.blit(FONT.render("Data Size", True, BLACK), (50, 85))
    screen.blit(FONT.render("Min Value", True, BLACK), (250, 85))
    screen.blit(FONT.render("Max Value", True, BLACK), (450, 85))
    screen.blit(FONT.render("Speed [sec]", True, BLACK), (650, 85))

    data_size_input.draw(screen)
    min_input.draw(screen)
    max_input.draw(screen)
    speed_input.draw(screen)
    start_button.draw(screen)
    generate_button.draw(screen)

    # Draw sorting bars
    pygame.draw.rect(screen, WHITE, (0, UI_HEIGHT, WIDTH, BAR_AREA_HEIGHT))
    if len(data) > 0:
        bar_width = WIDTH / len(data)
        max_data = max(data) if max(data) > 0 else 1
        for i, val in enumerate(data):
            bar_height = (val / max_data) * (BAR_AREA_HEIGHT - 20)
            x = i * bar_width
            y = HEIGHT - bar_height
            color = RED if i in highlight_indices else GRAY
            pygame.draw.rect(screen, color, (x, y, bar_width - 1, bar_height))
            if i in highlight_indices:
                pygame.draw.polygon(screen, RED, [
                    (x + bar_width / 2, y - 10),
                    (x + bar_width / 2 - 5, y),
                    (x + bar_width / 2 + 5, y)
                ])

    pygame.display.flip()
    clock.tick(60)

pygame.quit()
