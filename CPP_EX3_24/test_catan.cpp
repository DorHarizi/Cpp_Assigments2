#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Catan.hpp"
#include "ResourceType.hpp"
#include "DevelopmentCardType.hpp"

using namespace ariel;

// Player Tests
TEST_CASE("Player Creation") {
    Player player("Alice");
    CHECK(player.getName() == "Alice");
    CHECK(player.getPoints() == 0);
}

TEST_CASE("Player Resource Management") {
    Player player("Alice");

    SUBCASE("Add Resource") {
        player.addResource(ResourceType::Forest, 5);
        CHECK(player.getResourceCount(ResourceType::Forest) == 5);
    }

    SUBCASE("Use Resource") {
        player.addResource(ResourceType::Forest, 5);
        player.useResource(ResourceType::Forest, 3);
        CHECK(player.getResourceCount(ResourceType::Forest) == 2);
    }

    SUBCASE("Not Enough Resources") {
        CHECK_THROWS_AS(player.useResource(ResourceType::Forest, 1), std::runtime_error);
    }
}

TEST_CASE("Player Development Card Management") {
    Player player("Alice");

    SUBCASE("Buy Development Card") {
        player.addResource(ResourceType::Mountains, 1);
        player.addResource(ResourceType::Pasture, 1);
        player.addResource(ResourceType::Agricultural, 1);
        CHECK_NOTHROW(player.buyDevelopmentCard());
    }
}

// Board Tests
TEST_CASE("Board Initialization") {
    Board board;
    CHECK(board.getLandPlots().size() == 19);
}

TEST_CASE("Board Resource Distribution") {
    Board board;
    CHECK_NOTHROW(board.distributeResources());
}

TEST_CASE("Board Manual Setup") {
    Board board;
    std::vector<std::pair<int, std::pair<ResourceType, YieldType>>> setup = {
        {2, {ResourceType::Forest, YieldType::wood}},
        {3, {ResourceType::Hills, YieldType::bricks}},
        // Add more pairs to make up the 19 plots
    };
    CHECK_THROWS_AS(board.setupManualBoard(setup), std::invalid_argument);

    // Correct setup with 19 plots
    for (int i = 2; i <= 12; ++i) {
        setup.push_back({i, {ResourceType::Forest, YieldType::wood}});
    }
    CHECK_NOTHROW(board.setupManualBoard(setup));
}

// Catan Tests
TEST_CASE("Catan Game Setup") {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Catan game(player1, player2, player3);
    CHECK(game.getCurrentPlayer().getName() == "Alice");
}

TEST_CASE("Player Turn Rotation") {
    Player player1("Alice");
    Player player2("Bob");
    Player player3("Charlie");

    Catan game(player1, player2, player3);
    game.nextTurn();
    CHECK(game.getCurrentPlayer().getName() == "Bob");
    game.nextTurn();
    CHECK(game.getCurrentPlayer().getName() == "Charlie");
    game.nextTurn();
    CHECK(game.getCurrentPlayer().getName() == "Alice");
}

TEST_CASE("Build Road") {
    Player player("Alice");
    Catan game(player, player, player); // Simplified for single player testing

    std::vector<std::string> places = {"Forest"};
    std::vector<int> placesNum = {2};

    player.addResource(ResourceType::Hills, 1);
    player.addResource(ResourceType::Forest, 1);

    CHECK_NOTHROW(player.placeRoad(places, placesNum, game.getBoard()));
}

TEST_CASE("Build Settlement") {
    Player player("Alice");
    Catan game(player, player, player); // Simplified for single player testing

    std::vector<std::string> places = {"Forest"};
    std::vector<int> placesNum = {2};

    player.addResource(ResourceType::Hills, 1);
    player.addResource(ResourceType::Forest, 1);
    player.addResource(ResourceType::Pasture, 1);
    player.addResource(ResourceType::Agricultural, 1);

    CHECK_NOTHROW(player.placeSettelemnt(places, placesNum, game.getBoard()));
}

TEST_CASE("Build City") {
    Player player("Alice");
    Catan game(player, player, player); // Simplified for single player testing

    std::vector<int> placesNum = {2, 3};

    // Add initial settlement
    std::vector<std::string> places = {"Forest"};
    player.addResource(ResourceType::Hills, 1);
    player.addResource(ResourceType::Forest, 1);
    player.addResource(ResourceType::Pasture, 1);
    player.addResource(ResourceType::Agricultural, 1);
    player.placeSettelemnt(places, placesNum, game.getBoard());

    // Resources for city
    player.addResource(ResourceType::Mountains, 3);
    player.addResource(ResourceType::Agricultural, 2);

    CHECK_NOTHROW(player.placeCity(placesNum, game.getBoard()));
}

TEST_CASE("Trade Resources") {
    Player player1("Alice");
    Player player2("Bob");
    
    player1.addResource(ResourceType::Forest, 5);
    player2.addResource(ResourceType::Hills, 5);
    
    CHECK_NOTHROW(player1.trade(player2, "Forest", "Hills", 2, 2));
    CHECK(player1.getResourceCount(ResourceType::Forest) == 3);
    CHECK(player1.getResourceCount(ResourceType::Hills) == 2);
    CHECK(player2.getResourceCount(ResourceType::Forest) == 2);
    CHECK(player2.getResourceCount(ResourceType::Hills) == 3);
}

