const V4Coin = artifacts.require("V4Coin");
const DutchAuction = artifacts.require("DutchAuction");

module.exports = function (deployer) {
    deployer.deploy(V4Coin)
        .then(async (v4CoinInstance) => {
            const v4CoinAddress = v4CoinInstance.address;

            const startingPrice = 1000;
            const reservePrice = 100;
            const auctionDuration = 1200;
            const decrementAmount = 500;

            await deployer.deploy(
                DutchAuction,
                v4CoinAddress,
                startingPrice,
                reservePrice,
                auctionDuration,
                decrementAmount
            );
        });
};
