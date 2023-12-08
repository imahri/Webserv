<?php
// Define a class called "Car"
class Car
{
    private $brand;
    private $color;
    private $price;

    // Constructor
    public function __construct($brand, $color, $price)
    {
        $this->brand = $brand;
        $this->color = $color;
        $this->price = $price;
    }

    // Getter methods
    public function getBrand()
    {
        return $this->brand;
    }

    public function getColor()
    {
        return $this->color;
    }

    public function getPrice()
    {
        return $this->price;
    }

    // Method to calculate the discounted price
    public function calculateDiscountedPrice($percentage)
    {
        $discount = $this->price * ($percentage / 100);
        $discountedPrice = $this->price - $discount;
        return $discountedPrice;
    }
}

// Create car objects
$car1 = new Car("Toyota", "Blue", 20000);
$car2 = new Car("Honda", "Red", 25000);

// Output car information
echo "Car 1: " . $car1->getBrand() . ", " . $car1->getColor() . ", $" . $car1->getPrice() . "<br>";
echo "Car 2: " . $car2->getBrand() . ", " . $car2->getColor() . ", $" . $car2->getPrice() . "<br>";

// Calculate and output discounted prices
$discountPercentage = 10;
$car1DiscountedPrice = $car1->calculateDiscountedPrice($discountPercentage);
$car2DiscountedPrice = $car2->calculateDiscountedPrice($discountPercentage);

echo "Discounted Price for Car 1: $" . $car1DiscountedPrice . "<br>";
echo "Discounted Price for Car 2: $" . $car2DiscountedPrice . "<br>";
?>