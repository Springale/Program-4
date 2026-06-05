void Borrow::execute(Store& store) {
    Customer* c = store.getCustomer(customerID);
    Movie* m = store.inventory.findMovie(movieKey);

    if (!c || !m) return;

    if (m->getStock() <= 0) {
        cout << "Movie out of stock" << endl;
        return;
    }

    m->decreaseStock();
    c->addTransaction(this);
}