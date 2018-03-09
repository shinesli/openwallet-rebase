//
// Created by mwo on 5/11/15.
//

#ifndef XMREG01_TOOLS_H
#define XMREG01_TOOLS_H

#define PATH_SEPARARTOR '/'

#define XMR_AMOUNT(value) \
    static_cast<double>(value) / 1e12

#define REMOVE_HASH_BRAKETS(a_hash) \
    a_hash.substr(1, a_hash.size()-2)

#include "monero_headers.h"

#include "../ext/format.h"
#include "../ext/json.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>
#include <boost/optional.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include <string>
#include <vector>
#include <array>
#include <random>

/**
 * Some helper functions that might or might not be useful in this project.
 * Names are rather self-explanatory, so I think
 * there is no reason for any detailed explanations here
 */
namespace xmreg
{

using namespace cryptonote;
using namespace crypto;
using namespace std;

namespace bf = boost::filesystem;
namespace pt = boost::posix_time;
namespace gt = boost::gregorian;
namespace lt = boost::local_time;


using json = nlohmann::json;

using  epee::string_tools::pod_to_hex;
using  epee::string_tools::hex_to_pod;

template <typename T>
bool
parse_str_secret_key(const string& key_str, T& secret_key);


bool
get_tx_pub_key_from_str_hash(Blockchain& core_storage,
                         const string& hash_str,
                         transaction& tx);

bool
parse_str_address(const string& address_str,
                  account_public_address& address,
                  bool testnet = false);

inline bool
is_separator(char c);

string
print_address(const account_public_address& address,
              bool testnet = false);

string
print_sig (const signature& sig);

string
remove_trailing_path_separator(const string& in_path);

bf::path
remove_trailing_path_separator(const bf::path& in_path);


string
timestamp_to_str_gm(time_t timestamp, const char* format = "%F %T");

ostream&
operator<< (ostream& os, const account_public_address& addr);


string
get_default_lmdb_folder(bool testnet = false);

bool
generate_key_image(const crypto::key_derivation& derivation,
                   const std::size_t output_index,
                   const crypto::secret_key& sec_key,
                   const crypto::public_key& pub_key,
                   crypto::key_image& key_img);

bool
get_blockchain_path(bf::path& blockchain_path,
                    bool testnet = false);

array<uint64_t, 4>
summary_of_in_out_rct(
        const transaction& tx,
        vector<pair<txout_to_key, uint64_t>>& output_pub_keys,
        vector<txin_to_key>& input_key_imgs);

// this version for mempool txs from json
array<uint64_t, 6>
summary_of_in_out_rct(const json& _json);

uint64_t
sum_money_in_outputs(const transaction& tx);

pair<uint64_t, uint64_t>
sum_money_in_outputs(const string& json_str);

uint64_t
sum_money_in_inputs(const transaction& tx);

pair<uint64_t, uint64_t>
sum_money_in_inputs(const string& json_str);

array<uint64_t, 2>
sum_money_in_tx(const transaction& tx);

array<uint64_t, 2>
sum_money_in_txs(const vector<transaction>& txs);

uint64_t
sum_fees_in_txs(const vector<transaction>& txs);

uint64_t
get_mixin_no(const transaction& tx);

vector<uint64_t>
get_mixin_no(const string& json_str);

vector<uint64_t>
get_mixin_no_in_txs(const vector<transaction>& txs);

vector<pair<txout_to_key, uint64_t>>
get_ouputs(const transaction& tx);

vector<tuple<txout_to_key, uint64_t, uint64_t>>
get_ouputs_tuple(const transaction& tx);

vector<txin_to_key>
get_key_images(const transaction& tx);

bool
get_payment_id(const vector<uint8_t>& extra,
               crypto::hash& payment_id,
               crypto::hash8& payment_id8);

bool
get_payment_id(const transaction& tx,
               crypto::hash& payment_id,
               crypto::hash8& payment_id8);

inline double
get_xmr(uint64_t core_amount)
{
    return  static_cast<double>(core_amount) / 1e12;
}

array<size_t, 5>
timestamp_difference(uint64_t t1, uint64_t t2);

string
read(string filename);



pair<string, double>
timestamps_time_scale(const vector<uint64_t>& timestamps,
                  uint64_t timeN, uint64_t resolution = 80,
                  uint64_t time0 = 1397818193 /* timestamp of the second block */);


time_t
ptime_to_time_t(const pt::ptime& in_ptime);

bool
decode_ringct(const rct::rctSig & rv,
              const crypto::public_key &pub,
              const crypto::secret_key &sec,
              unsigned int i,
              rct::key & mask,
              uint64_t & amount);

bool
url_decode(const std::string& in, std::string& out);

map<std::string, std::string>
parse_crow_post_data(const string& req_body);

// from wallet2::decrypt
string
decrypt(const std::string &ciphertext,
        const crypto::secret_key &skey,
        bool authenticated = true);

// based on
// crypto::public_key wallet2::get_tx_pub_key_from_received_outs(const tools::wallet2::transfer_details &td) const
public_key
get_tx_pub_key_from_received_outs(const transaction &tx);


string
xmr_amount_to_str(const uint64_t& xmr_amount, string format="{:0.12f}");

bool
is_output_ours(const size_t& output_index,
               const transaction& tx,
               const public_key& pub_tx_key,
               const secret_key& private_view_key,
               const public_key& public_spend_key);

bool
get_real_output_for_key_image(const key_image& ki,
                              const transaction& tx,
                              const secret_key& private_view_key,
                              const public_key& public_spend_key,
                              uint64_t output_idx,
                              public_key output_pub_key);

// based on http://stackoverflow.com/a/9943098/248823
template<typename Iterator, typename Func>
void chunks(Iterator begin,
            Iterator end,
            iterator_traits<string::iterator>::difference_type k,
            Func f)
{
    Iterator chunk_begin;
    Iterator chunk_end;
    chunk_end = chunk_begin = begin;

    do
    {
        if(std::distance(chunk_end, end) < k)
            chunk_end = end;
        else
            std::advance(chunk_end, k);
        f(chunk_begin,chunk_end);
        chunk_begin = chunk_end;
    }
    while(std::distance(chunk_begin,end) > 0);
}

bool
make_tx_from_json(const string& json_str, transaction& tx);


inline
crypto::hash
generated_payment_id()
{
    return crypto::rand<crypto::hash>();
}

string
get_human_readable_timestamp(uint64_t ts);


string
make_hash(const string& in_str);

}

#endif //XMREG01_TOOLS_H
