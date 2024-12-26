std::vector<int> primes, phi, mu, minp;
void sieve(int n = 1e6)
{
    phi.resize(n+1); 
    minp = mu = phi;
    phi[1] = 1; mu[1] = 1;
    for(int i = 2; i <= n; ++i) {
        if(!minp[i]) {
            primes.push_back(i);
            phi[i] = i - 1, mu[i] = -1;
            minp[i] = i;
        }
        for(auto p: primes) {
            if(1ll * i * p > n) break;
            minp[i * p] = p;
            if(minp[i] == p) {   
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p; 
                break; 
            }
            phi[i * p] = phi[i] * phi[p];
            mu[i * p] = - mu[i];
        }
    }
}