-module(spooky).

-on_load(init/0).

-define(NOT_LOADED, not_loaded(?LINE)).

-export([hash128/3, hash128/1, hash64/2, hash64/1, hash32/2, hash32/1]).

hash128(_Term, _Seed1, _Seed2) -> ?NOT_LOADED.

hash128(_Term) -> ?NOT_LOADED.

hash64(_Term, _Seed) -> ?NOT_LOADED.

hash64(_Term) -> ?NOT_LOADED.

hash32(_Term, _Seed) -> ?NOT_LOADED.

hash32(_Term) -> ?NOT_LOADED.

init() ->
    PrivDir = case code:priv_dir(?MODULE) of
                  {error, _} ->
                      EbinDir = filename:dirname(code:which(?MODULE)),
                      AppPath = filename:dirname(EbinDir),
                      filename:join(AppPath, "priv");
                  Path ->
                      Path
              end,
    case erlang:load_nif(filename:join(PrivDir, "spooky.erl"), 0) of
        ok ->                  ok;
        {error,{reload, _}} -> ok;
        Error ->               Error
    end.

not_loaded(Line) ->
    erlang:nif_error({not_loaded, [{module, ?MODULE}, {line, Line}]}).
