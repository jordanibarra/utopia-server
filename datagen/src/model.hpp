#pragma once

#include <string>
#include "buffer.hpp"

struct User
{
    std::string first_name;
    std::string last_name;
    std::string email;

    inline Buffer serialize()
    {
        /**
         * Calculating the size of this struct in bytes to be serialized.
         * Strings will be prefix length encoded. So the length will be
         * serialized before the string itself, it replaces the null-termination
         * byte, and makes it easier to read later.
         */
        size_t sizeInBytes = first_name.size() * sizeof(char) + sizeof(uint8_t);
        sizeInBytes += last_name.size() * sizeof(char) + sizeof(uint8_t);
        sizeInBytes += email.size() * sizeof(char) + sizeof(uint8_t);

        Buffer buffer{sizeInBytes};
        buffer.write(first_name);
        buffer.write(last_name);
        buffer.write(email);

        return buffer;
    }
};

struct Card
{
    enum CardType : uint8_t
    {
        None = 0xFF,
        Amex = 0,
        Visa = 1,
        Mastercard = 2,
    };

    CardType type;
    uint8_t expiration_month;
    uint8_t expiration_year;
    uint cvv;
    std::string pan;

    inline Buffer serialize()
    {
        auto sizeInBytes
                = sizeof(uint8_t)
                + sizeof(expiration_month)
                + sizeof(expiration_year)
                + sizeof(cvv)
                + (sizeof(char) * pan.size());

        Buffer buffer{sizeInBytes};
        buffer.write((uint8_t)type);
        buffer.write(expiration_month);
        buffer.write(expiration_year);
        buffer.write(cvv);
        buffer.write(pan);

        return buffer;
    }
};

struct Merchant
{
    enum MerchantCategory : uint8_t
    {
        Agricultural,
        Contracted,
        TravelAndEntertainment,
        CarRental,
        Lodging,
        Transportation,
        Utility,
        RetailOutlet,
        ClothingStore,
        MiscStore,
        Business,
        ProfessionalOrMembership,
        Government
    };

    std::string name;
    uint mcc;
    MerchantCategory category;

    inline Buffer serialize()
    {
        auto sizeInBytes = (sizeof(char) * name.size()) + sizeof(mcc) + sizeof(uint8_t);

        Buffer buffer{sizeInBytes};
        buffer.write(name);
        buffer.write(mcc);
        buffer.write((uint8_t)category);

        return buffer;
    }
};
