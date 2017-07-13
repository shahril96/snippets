angular
.module('webui.services.configuration',  [])
.constant('$name', 'Aria2 WebUI')  // name used across the entire UI
.constant('$titlePattern', 'active: {active} - waiting: {waiting} - stopped: {stopped} — {name}')
.constant('$pageSize', 11)         // number of downloads shown before pagination kicks in
.constant('$authconf', {           // default authentication configuration, never fill it in case the webui is hosted in public IP as it can be compromised
  host: 'localhost',
  port: 6800,
  encrypt: false,
  auth: {                          // either add the token field or the user and pass field, not both.
  // token: '$YOUR_SECRET_TOKEN$'
  /*-----------------------------*/
  // user: '*YOUR_USERNAME*',
  // pass: '*YOUR_SECRET_PASS*'
  }
})
.constant('$enable', {

  torrent: true,  // bittorrent support only enabled if supported by aria2 build, set to false otherwise to permanently disable it
  metalink: true, // metalink support only enabled if supported by aria2 build, set to false to permanently disable it

  sidebar: {            // configuration related to the sidebar next to the list of downloads
    show: true,         // set to false to completely hide the sidebar. Other elements inside will be automatically hidden
    stats: true,        // set to false to hide the global statistic section (contains the speed graph for now)
    filters: true,      // set to false to hide the  Download Filters
    starredProps: true // only shown when at least one property is added to the starred list, set to false to permanently hide the Quick Access Settings inside the sidebar
  }
})
.constant('$starredProps', [   // default list of Quick Access Properties. Can be overridden by making modification through the Global Settings dialog
  // go to Global Settings dialog to see their description
  'dir', 'conf-path', 'seed-ratio', 'bt-max-open-files', 'bt-max-peers', 'bt-request-peer-speed-limit',  'bt-require-crypto', 'bt-min-crypto-level', 'max-download-limit', 'max-upload-limit'
])
.constant('$downloadProps', [ // Similar to starred Quick Access properties but for adding new downloads.
  // go to Advance Download Options when adding a new download to view the list of possible options
  'pause', 'dir', 'max-connection-per-server'
])
.constant('$globalTimeout', 500)  // interval to update the individual downloads
;
