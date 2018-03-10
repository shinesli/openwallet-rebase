var config = {
    apiUrl: "http://127.0.0.1:1984/",
    mainnetExplorerUrl: "https://moneroexplorer.com/",
    testnetExplorerUrl: "http://139.162.32.245:8082/",
    testnet: false,
    coinUnitPlaces: 9,
    txMinConfirms: 10,         // corresponds to CRYPTONOTE_DEFAULT_TX_SPENDABLE_AGE in Monero
    txCoinbaseMinConfirms: 20, // corresponds to CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW in Monero
    coinSymbol: 'ARS',
    openAliasPrefix: "ars",
    coinName: 'Aureus',
    coinUriPrefix: 'aureus:',
    addressPrefix: 49f4a,
    integratedAddressPrefix: 1fdd4a,
    addressPrefixTestnet: 0xc526,
    integratedAddressPrefixTestnet: 0x3cdd25,
    feePerKB: new JSBigInt('2000000000'),//20^10 - for testnet its not used, as fee is dynamic.
    dustThreshold: new JSBigInt('1000000000'),//10^10 used for choosing outputs/change - we decompose all the way down if the receiver wants now regardless of threshold
    txChargeRatio: 0.5,
    defaultMixin: 1, // minimum mixin for hardfork v5
    txChargeAddress: '',
    idleTimeout: 30,
    idleWarningDuration: 20,
    maxBlockNumber: 500000000,
    avgBlockTime: 60,
    debugMode: false
};
