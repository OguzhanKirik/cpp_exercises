#include "SDL.h"

void drawCircle(SDL_Renderer* renderer, SDL_Point cell, int cell_size) {
    int radius = cell_size / 2 - 1; // Padding to stay inside the cell
    int cx = cell.x + cell_size / 2;
    int cy = cell.y + cell_size / 2;

    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        SDL_RenderDrawPoint(renderer, cx + x, cy + y);
        SDL_RenderDrawPoint(renderer, cx + y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - y, cy + x);
        SDL_RenderDrawPoint(renderer, cx - x, cy + y);
        SDL_RenderDrawPoint(renderer, cx - x, cy - y);
        SDL_RenderDrawPoint(renderer, cx - y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + y, cy - x);
        SDL_RenderDrawPoint(renderer, cx + x, cy - y);

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}



void drawTriangle(SDL_Renderer* renderer, SDL_Point cell, int cell_size) {
    int x = cell.x;
    int y = cell.y;

    // Triangle vertices within the cell (upward-pointing triangle)
    int x1 = x + cell_size / 2;  // top-center
    int y1 = y;

    int x2 = x;                  // bottom-left
    int y2 = y + cell_size;

    int x3 = x + cell_size;      // bottom-right
    int y3 = y + cell_size;

    // Helper: draw a horizontal line
    auto drawScanline = [&](int y, int x_start, int x_end) {
        if (x_start > x_end) std::swap(x_start, x_end);
        SDL_RenderDrawLine(renderer, x_start, y, x_end, y);
    };

    // Linear interpolation of x for given y
    auto interpolate = [](int y0, int y1, int x0, int x1, int y) {
        if (y1 == y0) return x0;
        return x0 + (x1 - x0) * (y - y0) / (y1 - y0);
    };

    // Sort by y
    if (y2 < y1) { std::swap(x1, x2); std::swap(y1, y2); }
    if (y3 < y1) { std::swap(x1, x3); std::swap(y1, y3); }
    if (y3 < y2) { std::swap(x2, x3); std::swap(y2, y3); }

    // Top half
    for (int yi = y1; yi <= y2; yi++) {
        int xa = interpolate(y1, y3, x1, x3, yi);
        int xb = interpolate(y1, y2, x1, x2, yi);
        drawScanline(yi, xa, xb);
    }

    // Bottom half
    for (int yi = y2 + 1; yi <= y3; yi++) {
        int xa = interpolate(y1, y3, x1, x3, yi);
        int xb = interpolate(y2, y3, x2, x3, yi);
        drawScanline(yi, xa, xb);
    }
}
