void Store::processCommands(const std::string &filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        std::cerr << "error: could not open commands file: " << filename << std::endl;
        return;
    }

    std::string line;

    while (std::getline(infile, line))
    {
        if (line.empty()) continue;

        // create transaction using factory
        Transaction* trans = TransactionFactory::createTransaction(line, *this);

        if (trans != nullptr)
        {
            trans->execute(*this);

            // Delete transaction if:
            // 1. It's a temporary type (History or DisplayInventory), OR
            // 2. It's a Borrow/Return that FAILED (success == false)
            bool isTemporary = (dynamic_cast<History*>(trans) != nullptr ||
                                dynamic_cast<DisplayInventory*>(trans) != nullptr);
            
            bool isFailedBorrowReturn = (!isTemporary && !trans->wasSuccessful());
            
            if (isTemporary || isFailedBorrowReturn)
            {
                delete trans;
            }
            // Successful Borrow/Return are owned by Customer - don't delete here
        }
    }
}
