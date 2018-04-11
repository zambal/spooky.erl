#include "erl_nif.h"
#include "SpookyV2.h"

#define __UNUSED(v) ((void)(v))

#define SEED1 0x2AA43B55
#define SEED2 0xA49026C0

static ERL_NIF_TERM shv2_hash128(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint64_t hash1, hash2;

  ERL_NIF_TERM hash128;

  if(!(argc == 3 &&
      enif_get_uint64(env, argv[1], &hash1) &&
      enif_get_uint64(env, argv[2], &hash2))) {
    return enif_make_badarg(env);
  }

  if(enif_term_to_binary(env, argv[0], &message)) {
    SpookyHash::Hash128(message.data, message.size, &hash1, &hash2);
    uint64_t *buf = (uint64_t *)enif_make_new_binary(env, 16, &hash128);
    buf[0] = hash1; buf[1] = hash2;

    return hash128;
  }
  else {
    return enif_make_badarg(env);
  }
}

static ERL_NIF_TERM shv2_hash128_noseed(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint64_t hash1 = SEED1, hash2 = SEED2;

  ERL_NIF_TERM hash128;

  if(argc != 1) {
    return enif_make_badarg(env);
  }

  if(enif_term_to_binary(env, argv[0], &message)) {
    SpookyHash::Hash128(message.data, message.size, &hash1, &hash2);
    uint64_t *buf = (uint64_t *)enif_make_new_binary(env, 16, &hash128);
    buf[0] = hash1; buf[1] = hash2;

    return hash128;
  }
  else {
    return enif_make_badarg(env);
  }
}

static ERL_NIF_TERM shv2_hash64(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint64_t seed;

  if(!(argc == 2 &&
      enif_get_uint64(env, argv[1], &seed))) {
    return enif_make_badarg(env);
  }

  if(enif_term_to_binary(env, argv[0], &message)) {
    return enif_make_uint64(env, SpookyHash::Hash64(message.data, message.size, seed));
  }
  else {
    return enif_make_badarg(env);
  }
}

static ERL_NIF_TERM shv2_hash64_noseed(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint64_t seed = SEED1;

  if(argc != 1) {
    return enif_make_badarg(env);
  }


  if(enif_term_to_binary(env, argv[0], &message)) {
    return enif_make_uint64(env, SpookyHash::Hash64(message.data, message.size, seed));
  }
  else {
    return enif_make_badarg(env);
  }
}

static ERL_NIF_TERM shv2_hash32(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint32_t seed;

  if(!(argc == 2 &&
      enif_get_uint(env, argv[1], &seed))) {
    return enif_make_badarg(env);
  }

  if(enif_term_to_binary(env, argv[0], &message)) {
    return enif_make_uint(env, SpookyHash::Hash32(message.data, message.size, seed));
  }
  else {
    return enif_make_badarg(env);
  }
}

static ERL_NIF_TERM shv2_hash32_noseed(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
  ErlNifBinary message;
  uint32_t seed = SEED1;

  if(argc != 1) {
    return enif_make_badarg(env);
  }


  if(enif_term_to_binary(env, argv[0], &message)) {
    return enif_make_uint(env, SpookyHash::Hash32(message.data, message.size, seed));
  }
  else {
    return enif_make_badarg(env);
  }
}


static ErlNifFunc nif_funcs[] =
{
  {"hash128", 3, shv2_hash128},
  {"hash128", 1, shv2_hash128_noseed},
  {"hash64", 2, shv2_hash64},
  {"hash64", 1, shv2_hash64_noseed},
  {"hash32", 2, shv2_hash32},
  {"hash32", 1, shv2_hash32_noseed}
};

ERL_NIF_INIT(spooky, nif_funcs, NULL, NULL, NULL, NULL);

