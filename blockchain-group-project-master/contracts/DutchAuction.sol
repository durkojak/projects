// SPDX-License-Identifier: MIT
pragma solidity ^0.8.2;

import "@openzeppelin/contracts/security/ReentrancyGuard.sol";
import "./V4Coin.sol";


contract DutchAuction is ReentrancyGuard {
    V4Coin public token;
    address payable public seller;
    uint256 public startingPrice;
    uint256 public reservePrice;
    uint256 public duration;
    uint256 public startAt;
    uint256 public endAt;
    uint256 public totalTokens;
    uint256 public tokensSold;
    bool public auctionEnded;

    mapping(address => uint256) public bids;

    event BidPlaced(address indexed bidder, uint256 amount, uint256 tokensPurchased);
    event AuctionEnded(uint256 totalTokensSold, uint256 clearingPrice);
    event debugBurn(uint256 value);
    event Debug(string message);

    constructor(
        address _tokenAddress,
        uint256 _startingPrice,
        uint256 _reservePrice,
        uint256 _duration,
        uint256 _totalTokens
    ) {
        require(_startingPrice > _reservePrice, "Starting price must be greater than reserve price");
        token = V4Coin(_tokenAddress);
        seller = payable(msg.sender);
        startingPrice = _startingPrice;
        reservePrice = _reservePrice;
        duration = _duration;
        startAt = block.timestamp;
        endAt = startAt + duration;
        totalTokens = _totalTokens;


    }
    
    function getAuctionEnded() public view returns (bool) {
        return auctionEnded;
    }
    function getStartingPrice() public view returns (uint256) {
        return startingPrice;
    }
    function getReservePrice() public view returns (uint256) {
        return reservePrice;
    }
    function getDuration() public view returns (uint256) {
        return duration;
    }
    function getEndAt() public view returns (uint256) {
        return endAt;
    }
    function getStartTime() public view returns (uint256) {
        return startAt;
    }
    function getCurrentPrice() public view returns (uint256) {
        uint256 currentTime = block.timestamp;
        uint256 currentPrice;

        if (currentTime >= endAt) {
            currentPrice = reservePrice;
        } else {
            uint256 elapsed = currentTime - startAt;
            uint256 priceDecay = ((startingPrice - reservePrice) * elapsed) / duration;
            currentPrice = startingPrice - priceDecay;
        }



        return currentPrice;
    }

    function bid() public payable nonReentrant {

        require(block.timestamp >= startAt && block.timestamp <= endAt, "Auction not active");
        uint256 price = getCurrentPrice();
        uint256 tokensToPurchase = ((msg.value) / price); // Adjust for decimals
        require(tokensSold + tokensToPurchase <= totalTokens, "Not enough tokens left");

        bids[msg.sender] += msg.value;
        tokensSold += tokensToPurchase;

        bool success = token.transfer(msg.sender, tokensToPurchase);
        require(success, "Token transfer failed");



        emit BidPlaced(msg.sender, msg.value, tokensToPurchase);

        if (tokensSold >= totalTokens) {
            emit AuctionEnded(tokensSold, price);
        }
    }

    function endAuction() public nonReentrant {
        emit debugBurn(1337);
        finalizeAuction();
    }

    function finalizeAuction() internal {
        uint256 tokensToBurn = totalTokens - tokensSold;
        emit debugBurn(tokensToBurn);
        if (tokensToBurn > 0) {
            token.burn(tokensToBurn);
            emit debugBurn(tokensToBurn);
        }
    }
}