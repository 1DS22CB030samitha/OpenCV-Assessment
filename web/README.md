# Edge Detection Viewer - Web Component

TypeScript-based web viewer for displaying processed frames from the Android edge detection application.

## Setup

```bash
npm install
npm run build
```

## Development

```bash
npm run dev  # Watch mode for TypeScript compilation
```

## Usage

Open `index.html` in a web browser or serve via HTTP server:

```bash
python -m http.server 8000
```

Then navigate to `http://localhost:8000`

## Architecture

- `viewer.ts`: Core viewer class with frame display and statistics
- `index.ts`: Main entry point and initialization
- `index.html`: Web interface
- `styles.css`: Styling

## Integration

In a production environment, frames would be transmitted from the Android app via:
- WebSocket connection
- HTTP REST endpoint
- Base64 encoded image data

