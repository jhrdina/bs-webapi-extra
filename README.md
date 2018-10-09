# bs-webapi-extra

Playground for implementing various missing Web API bindings for ReasonML/BuckleScript, namely:

- WebRTC
- IndexedDB
- WebCrypto (so far only RSASSA-PKCS1-v1_5 and SHA-256 supported)
- WebSockets
- Encoding (TextEncoder, TextDecoder)

**DISCLAIMER:** Not all API methods from W3 standards are implemented and functions signatures may change from commit to commit in here. I plan to merge these APIs into the original bs-webapi-incubator as soon as the typical use cases feel comfortable to use.

# Build

```
npm run build
```

# Build + Watch

```
npm run start
```

# Run Examples

Examples are compiled during `npm run build`.

Create a single `app.js` file for browser using

```
npm run pack
```

Open `example/example.html` in your web browser. You don't need a running web server.

# Editor

If you use `vscode`, Press `Windows + Shift + B` it will build automatically
