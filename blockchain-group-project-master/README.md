# Dutch Auction

## Quick overview of program functionalities:
The program implements the Dutch Auction of our self deployed token V4Coin. The mechanism of the Dutch Auction, after an agreement with the professor, was modified in a way, that the amount of tokens you get depends only on the time you bid. The later you buy, the more you get, but it is not guaranteed that the tokens will still be avaliable later during the auction. This allows people to strategize when buying the token. After placing a successfull bid, the bidder immediately gets the amount of the tokens bought.

### How to run Auction:
1. Run Ganache
2. In contracts folder build & deploy contracts
3. Link Ganache to truffle-config.js
4. Update coin and auction addresses in script.js based on the deployed ones in ganache
5. Open index.html, place bid of like 1000 and provide account address as the bidder

### Ending the Auction:
After running and deploying an auction, there are two ways to finish the auction:
1. Wait for the time of the auction to run out. After the time runs out, all the unsold tokens are getting burned.
2. Buy out all tokens that are available. Buying out the last token is only available if you place a bid that will not exceed the price of the remaining tokens.

### Configuring the Auction:
Arguments of the auction
`
startingPrice
reservePrice
auctionDuration
decrementAmount
`
can be configured in 'migrations\2_deploy_contracts.js'.

## Creators:
Jakub Durkovic N2401408A
Maksymilian Tomaszewski N2400918E
Jakub Vonasek N24010011H