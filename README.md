# bs-webapi-extra

Playground for implementing various missing Web API bindings for ReasonML/BuckleScript, namely:

- WebRTC
- IndexedDB ([example](example/IDBExample.re))
- WebCrypto ([example](example/CryptoExample.re))
  - So far only RSASSA-PKCS1-v1_5 and SHA-256 is supported
- Navigator offline/online events ([example](example/NavigatorExample.re))
- WebSockets ([example](example/WebsocketsExample.re))
- Encoding (TextEncoder, TextDecoder)

**DISCLAIMER:** Not all API methods from W3 standards are implemented and functions signatures may change from commit to commit in here. I plan to merge these APIs into the original [bs-webapi-incubator](https://github.com/reasonml-community/bs-webapi-incubator) as soon as the typical use cases feel comfortable to use.

## Use

```
npm install bs-webapi-extra
```

and add a corresponding item to the `bsconfig.json`:

```json
"bs-dependencies": ["bs-webapi-extra"],
```

## Development

### Build

```
npm run build
```

### Build + Watch

```
npm run start
```

### Run Examples

Examples are compiled during `npm run build`.

Create a single `app.js` file for browser using

```
npm run pack
```

Open `example/example.html` in your web browser. You don't need a running web server.

Feel free to comment out examples you're not interested in inside the `example/example.re` file.

### Editor

If you use `vscode`, Press `Windows + Shift + B` it will build automatically
