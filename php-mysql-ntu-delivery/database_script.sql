-- creation of Canteen table
CREATE TABLE canteen (
    id_canteen INT PRIMARY KEY,
    canteen_name VARCHAR(255),
    canteen_location VARCHAR(255)
);

-- inserts into this table

INSERT INTO canteen (id_canteen, canteen_name, canteen_location) VALUES (1, 'Campus Bistro', 'North Wing');
INSERT INTO canteen (id_canteen, canteen_name, canteen_location) VALUES (2, 'Green Eats', 'East Wing');
INSERT INTO canteen (id_canteen, canteen_name, canteen_location) VALUES (3, 'Food Junction', 'West Wing');
INSERT INTO canteen (id_canteen, canteen_name, canteen_location) VALUES (4, 'Snack Station', 'South Wing');



-- creating table Stall

CREATE TABLE stall (
    id_stall INT PRIMARY KEY,
    id_canteen INT,
    stall_name VARCHAR(255),
    FOREIGN KEY (id_canteen) REFERENCES canteen(id_canteen)
);


-- Stalls for Canteen with id_canteen = 1
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (1, 1, 'Bistro Express');
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (2, 1, 'Healthy Bites');

-- Stalls for Canteen with id_canteen = 2
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (3, 2, 'Green Bowl');
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (4, 2, 'Daily Grinds');
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (5, 2, 'Fruit Fusion');

-- Stalls for Canteen with id_canteen = 3
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (6, 3, 'Foodie Hub');
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (7, 3, 'Snack Shack');
INSERT INTO stall (id_stall, id_canteen, stall_name) VALUES (8, 3, 'The Grill House');

-- No inserts for Canteen with id_canteen = 4 as per your request.

-- item_menu table

CREATE TABLE item_menu (
    id_item_menu INT PRIMARY KEY,
    id_stall INT,
    item_name VARCHAR(255),
    item_description TEXT,
    item_price DECIMAL(10, 2),
    FOREIGN KEY (id_stall) REFERENCES stall(id_stall)
);

-- Inserts into item_menu

-- Items for Stall with id_stall = 1 (Bistro Express)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (1, 1, 'Grilled Chicken Sandwich', 'A juicy grilled chicken sandwich with fresh lettuce and tomatoes', 6.50);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (2, 1, 'Vegetarian Wrap', 'A healthy wrap filled with fresh vegetables and hummus', 5.00);

-- Items for Stall with id_stall = 2 (Healthy Bites)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (3, 2, 'Quinoa Salad', 'A fresh salad with quinoa, avocado, and a lemon vinaigrette', 7.25);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (4, 2, 'Smoothie Bowl', 'A tropical smoothie bowl topped with granola and fresh fruits', 6.00);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (5, 2, 'Avocado Toast', 'Smashed avocado on multigrain toast with a sprinkle of chili flakes', 5.50);

-- Items for Stall with id_stall = 3 (Green Bowl)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (6, 3, 'Caesar Salad', 'Classic Caesar salad with crispy croutons and Parmesan', 6.75);

-- Items for Stall with id_stall = 4 (Daily Grinds)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (7, 4, 'Espresso', 'Rich and smooth espresso shot', 2.50);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (8, 4, 'Cappuccino', 'Creamy cappuccino with a hint of cocoa', 3.25);

-- Items for Stall with id_stall = 5 (Fruit Fusion)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (9, 5, 'Mango Smoothie', 'Refreshing mango smoothie with a touch of honey', 4.50);

-- Items for Stall with id_stall = 6 (Foodie Hub)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (10, 6, 'Beef Burger', 'Juicy beef patty with cheese and caramelized onions', 8.00);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (11, 6, 'French Fries', 'Crispy and golden French fries', 3.00);

-- Items for Stall with id_stall = 7 (Snack Shack)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (12, 7, 'Hot Dog', 'Classic hot dog with ketchup and mustard', 4.00);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (13, 7, 'Nachos', 'Cheesy nachos with jalapeños and salsa', 5.50);

-- Items for Stall with id_stall = 8 (The Grill House)
INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (14, 8, 'BBQ Ribs', 'Tender BBQ ribs with house sauce', 12.50);

INSERT INTO item_menu (id_item_menu, id_stall, item_name, item_description, item_price) 
VALUES (15, 8, 'Grilled Veggies', 'A mix of grilled seasonal vegetables', 5.75);


-- user table

CREATE TABLE users (
    id_user INT AUTO_INCREMENT PRIMARY KEY,
    first_name VARCHAR(255) NOT NULL,
    surname VARCHAR(255) NOT NULL,
    email VARCHAR(255) NOT NULL UNIQUE,
    password_hash VARCHAR(255) NOT NULL
);

-- order table

CREATE TABLE orders (
    id_order INT AUTO_INCREMENT PRIMARY KEY,
    id_user INT NOT NULL,
    status ENUM('pending', 'completed', 'canceled') NOT NULL DEFAULT 'pending',
    FOREIGN KEY (id_user) REFERENCES users(id_user)
);


-- order_menu_item to sort out M:N relation

CREATE TABLE order_menu_item (
    id_order INT NOT NULL,
    id_item_menu INT NOT NULL,
    quantity INT NOT NULL,
    PRIMARY KEY (id_order, id_item_menu),
    FOREIGN KEY (id_order) REFERENCES orders(id_order),
    FOREIGN KEY (id_item_menu) REFERENCES item_menu(id_item_menu)
);

-- creation of the review table

CREATE TABLE review (
    id_review INT AUTO_INCREMENT PRIMARY KEY,
    id_user INT NOT NULL,
    id_stall INT NOT NULL,
    rating INT CHECK (rating BETWEEN 1 AND 5),
    review_text TEXT,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (id_user) REFERENCES users(id_user),
    FOREIGN KEY (id_stall) REFERENCES stall(id_stall)
);

