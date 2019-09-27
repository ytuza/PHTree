#include <vector>
#include <ctime>  
#include <cstdlib>  

using namespace std;

typedef vector<vector<bool>> m_bool;
typedef vector<vector<vector<bool>>> c_bool;

class PHtree
{
public:
	PHtree(int d);
	PHtree(int d, m_bool n, int dn);

	PHtree(int d, m_bool n);
	~PHtree();

	int dim_max;


	int dim_now;

	m_bool data;
	vector<bool> fix;
	vector<PHtree*> HC;
	
	
	bool is_fix;

	bool find(m_bool *p, PHtree **pht);

	bool findWpath(m_bool *p, vector<PHtree*> *pht);
	bool insert(m_bool *point);
	m_bool fxc(m_bool *val);

	c_bool knn(m_bool *point, int n);

	void todos(c_bool *rpta, PHtree* pht, m_bool val);

private:

};

PHtree::PHtree(int d)
{
	dim_max = d;
	dim_now = 0;
	is_fix = true;
}

PHtree::PHtree(int d, m_bool n)
{
	m_bool rpta = fxc(&n);
	dim_max = d;
	dim_now = 0;
	is_fix = true;
	fix = rpta[0];
	if (n.size() > 1)
		HC.push_back(new PHtree(d, m_bool(rpta.begin()+1, rpta.end()), 1));
}

PHtree::PHtree(int d, m_bool n, int dn)
{
	dim_max = d;
	dim_now = dn;
	is_fix = true;
	fix = n[0];
	if(n.size()>1)
		HC.push_back(new PHtree (d,m_bool(n.begin()+1,n.end()),dn+1));
}

m_bool PHtree::fxc(m_bool *val) {
	
	m_bool rpta;

	for (int i = 0; i < (*val)[0].size(); i++) {
		vector<bool> tem;
		for (int j = 0; j < (*val).size(); j++) {
			tem.push_back((*val)[j][i]);
		}
		rpta.push_back(tem);
	}
	return rpta;
}

bool PHtree::find(m_bool *p, PHtree **pht) {
	*pht = this;
	if (is_fix) {
		if (fix == (*p)[dim_now]) {
			if (dim_now == dim_max-1) {
				return true; 
			}
			else {
				return HC[0]->find(p, pht);
			}
		}
		return false;
	}
	else {
		for (int i = 0; i < data.size(); i++) {
			if (data[i] == (*p)[dim_now]) {
				if (dim_now == dim_max -1) {
					return true;
				}
				else {
					return HC[i]->find(p,pht);
				}
			}

		}
		return false;
	}
}

bool PHtree::findWpath(m_bool *p, vector<PHtree*> *pht) {
	pht->push_back(this);
	
	if (is_fix) {
		if (fix == (*p)[dim_now]) {
			if (dim_now == dim_max - 1) {
				return true;
			}
			else {
				return HC[0]->findWpath(p, pht);
			}
		}
		return false;
	}
	else {
		for (int i = 0; i < data.size(); i++) {
			if (data[i] == (*p)[dim_now]) {
				if (dim_now == dim_max - 1) {
					return true;
				}
				else {
					return HC[i]->findWpath(p, pht);
				}
			}

		}
		return false;
	}
}

bool PHtree::insert(m_bool *point)
{
	m_bool p = fxc(point);
	PHtree *pht;

	if (find(&p, &pht)) {
		return false;
	}

	if (pht->is_fix) {
		pht->is_fix = false;
		pht->data.push_back(pht->fix);
		pht->fix.clear();
	}

	pht->data.push_back(p[pht->dim_now]);

	if (pht->dim_now != dim_max - 1)
		pht->HC.push_back(new PHtree(dim_max,m_bool(p.begin()+pht->dim_now+1,p.end()), pht->dim_now+1));

	return true;
}



void PHtree::todos(c_bool *rpta, PHtree *pht, m_bool val){
	
	vector<bool> noc = val[val.size()-1];
	
	val.pop_back();

	if (pht->dim_now == pht->dim_max - 1) {
		if (pht->is_fix) {
			if (pht->fix != noc) {
				val.push_back(pht->fix);
				rpta->push_back(val);
			}
			
		}
		else {
			for (size_t i = 0; i < pht->data.size(); i++)
			{
				if (pht->data[i] != noc) {
					val.push_back(pht->data[i]);
					rpta->push_back(val);
					val.pop_back();
				}			

			}
		}
	}
	else {


		if (pht->is_fix) {
			if (pht->fix != noc) {
				val.push_back(pht->fix);

				todos(rpta, pht->HC[0], val);
			}
			
			

		}
		else {
			for (size_t i = 0; i < pht->data.size(); i++)
			{
				if (pht->data[i] != noc) {
					val.push_back(pht->data[i]);
					todos(rpta, pht->HC[i], val);
					val.pop_back();
				}
				
			}
		}

		
	}
}

c_bool PHtree::knn(m_bool *point, int n) {
	vector<PHtree*> pht;
	c_bool rpta;
	m_bool p = fxc(point), tem = p;


	cout << "resultado b" << findWpath(&p, &pht) << endl;

	int itera = pht.size()-1;
	while (rpta.size() < n && itera >= 0) {
		todos(&rpta,pht[itera],p);
		p.pop_back();
		itera--;
	}

	return rpta;
}

PHtree::~PHtree()
{
}