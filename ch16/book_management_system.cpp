#include <compare>
#include <iostream>
#include <string>

using namespace std;

enum class Category {
  NOVEL,
  FICTION,
  NON_FICTION,
  SF,
  ESSAY,
};

class Book {
 public:
  Book() {
    title_ = "book0";
    author_ = "author0";
    publication_year_ = 0;
    price_ = 1000000;
    isbn_ = "isbn0";
    rental_count_ = 0;
    category_ = NOVEL;
  };

  Book(string title,
       string author,
       int publication_year,
       int price,
       string isbn,
       int rental_count,
       Category category)
      : title_(title),
        author_(author),
        publication_year_(publication_year),
        price_(price),
        isbn_(isbn),
        rental_count_(rental_count),
        category_(category) {};
  std::weak_ordering operator<=>(const Book& operand) const {
    if (publication_year_ != operand.publication_year_) {
      return publication_year_ <=> operand.publication_year_;
    }
    if (isbn_ != operand.isbn_) {
      return isbn_ <=> operand.isbn_;
    }
    if (rental_count_ != operand.rental_count_) {
      return rental_count_ <=> operand.rental_count_;
    }
    return std::weak_ordering::equivalent;
  };

  string GetCategoryString() {
    switch(category_) {
      case NOVEL:
        return "novel";
      case NON_FICTION:
        return "non-fiction";
      case FICTION:
        return "fiction";
      case SF:
        return "sf";
      case ESSAY:
        return "essay";
    }
    return "";
  };
  
  using enum Category;

  string title_;
  string author_;
  int publication_year_;
  int price_;
  string isbn_;
  int rental_count_;
  Category category_;
};

class FinalBook final : public Book {};

int main() {
  std::vector<Book> book_list;

  book_list.push_back(Book("book1", "author1", 2000, 12000, "isbn1", 3, Book::NOVEL));
  book_list.push_back(Book("book2", "author2", 2003, 15000, "isbn2", 3, Book::FICTION));
  book_list.push_back(Book("book3", "author3", 1999, 10000, "isbn3", 2, Book::NON_FICTION));
  book_list.push_back(Book("book4", "author4", 2005, 10000, "isbn4", 5, Book::SF));
  book_list.push_back(Book("book5", "author5", 2005, 18000, "isbn4", 1, Book::ESSAY));

  sort(book_list.begin(), book_list.end());

  for (auto& book : book_list) {
    cout << "Book(" << book.title_ << ", " << book.author_ << ", "
         << book.publication_year_ << ", " << book.price_ << ", " << book.isbn_
         << ", " << book.rental_count_ << ", " << book.GetCategoryString()
         << ")" << endl;
  }

  return 0;
}